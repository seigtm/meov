#include "core/resources/loader/impl/assimp_loader.hpp"
#include <benchmark/benchmark.hpp>

namespace {

[[nodiscard]] constexpr meov::core::resources::Texture::Type assimpTextureTypeToMEOV(
    const aiTextureType type) noexcept {
    using Type = meov::core::resources::Texture::Type;
    switch(type) {
        case aiTextureType_DIFFUSE: return Type::Diffuse;
        case aiTextureType_SPECULAR: return Type::Specular;
        case aiTextureType_HEIGHT: return Type::Height;
        case aiTextureType_NORMALS: return Type::Normal;
        case aiTextureType_AMBIENT: return Type::Ambient;
        default:
            break;
    };
    return Type::Invalid;
}

[[nodiscard]] meov::core::Vertex::color_type extractColor(const aiMesh *mesh,
    const meov::u32 index) noexcept {
    assert(mesh != nullptr);
    using namespace meov::core;
    if(const auto *mesh_color{ mesh->mColors[0] }; mesh_color != nullptr) {
        return Vertex::color_type{
            mesh_color->r,
            mesh_color->g,
            mesh_color->b,
            mesh_color->a
        };
    } else if (const auto *mesh_normals{ mesh->mNormals }; mesh_normals != nullptr) {
        return Vertex::color_type{
            mesh_normals[index].x,
            mesh_normals[index].y,
            mesh_normals[index].z,
            1.0f
        };
    }
    return Vertex::color_type{ 1.0f, 1.0f, 1.0f, 1.0f };
}

[[nodiscard]] meov::core::Vertex::tex_coords_type extractTexCoordinates(const aiMesh *mesh,
    const meov::u32 index) noexcept {
    assert(mesh != nullptr);
    using namespace meov::core;
    if(const auto *mesh_texture_coords{ mesh->mTextureCoords[0] }; mesh_texture_coords != nullptr) {
        return Vertex::tex_coords_type{
            mesh_texture_coords[index].x,
            mesh_texture_coords[index].y
        };
    }
    return Vertex::tex_coords_type{ 0.0f, 0.0f };
}

}  // anonymous namespace


namespace meov::core::resources {

sptr<meov::core::Model> AssimpLoader::LoadModel(const fs::path &path) {
    Assimp::Importer importer;
    const aiScene *scene{ importer.ReadFile(path.string(), aiProcess_Triangulate) };
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOGE << importer.GetErrorString();
        return nullptr;
    }
    if(!scene->HasMeshes()) {
        LOGI << "No meshes in model. Breaking load process.";
        return nullptr;
    }
    mLastLoadingDirectory = path.parent_path();
    if(scene->HasMaterials()) {
        PreLoadMaterials(scene->mMaterials, scene->mNumMaterials);
    }

    std::vector<sptr<Mesh>> meshes;
    meshes.reserve(scene->mNumMeshes);
    for(size_t i{}; i < scene->mNumMeshes; ++i) {
        auto as_mesh{ scene->mMeshes[i] };
        if(auto mesh{ ProcessMesh(as_mesh, scene) }; mesh) {
            mesh->Rename(std::string{ as_mesh->mName.C_Str() });
            meshes.emplace_back(std::move(mesh));
        }
    }
    return std::make_shared<Model>(std::move(meshes));
}

sptr<meov::core::Mesh> AssimpLoader::ProcessMesh(aiMesh *mesh, const aiScene *scene) const {
    std::vector<meov::core::Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    // Get vertices.
    #pragma omp parallel for
    for(u32 i{}; i < mesh->mNumVertices; ++i) {
        const auto &vertex{ mesh->mVertices[i] };
        vertices.emplace_back(
            Vertex::position_type{ vertex.x, vertex.y, vertex.z },
            extractColor(mesh, i),
            extractTexCoordinates(mesh, i)
        );
    }

    // Get indices from faces.
    const auto size{
        std::accumulate(mesh->mFaces, mesh->mFaces + mesh->mNumFaces, 0,
            [](u32 i, aiFace &face) { return i + face.mNumIndices; })
    };
    std::vector<u32> indices;
    indices.reserve(size);
    for(u32 i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        indices.insert(std::end(indices), face.mIndices, face.mIndices + face.mNumIndices);
    }

    // Process materials.
    Material material{ mCachedMaterials.at(mesh->mMaterialIndex) };
    return std::make_shared<Mesh>(std::move(vertices), std::move(indices), std::move(material));
}

void AssimpLoader::PreLoadMaterials(aiMaterial **materials, size_t count) {
    static constexpr std::array textureTypes{
        aiTextureType_DIFFUSE,
        aiTextureType_SPECULAR,
        aiTextureType_AMBIENT,
        aiTextureType_HEIGHT,
        aiTextureType_NORMALS
    };

    #pragma omp parallel
    for(size_t i{}; i < count; ++i) {
        const aiMaterial *material{ materials[i] };
        Material cache;
        if (f32 shininess{ cache.GetShininess() }; material->Get(AI_MATKEY_SHININESS, shininess) == aiReturn_SUCCESS) {
            cache.SetShininess(shininess);
        }
        for(const auto &type : textureTypes) {
            const auto textures{ material->GetTextureCount(type) };
            for(size_t index{}; index < textures; ++index) {
                if(aiString name{}; material->GetTexture(type, index, &name) == aiReturn_SUCCESS) {
                    const auto realType{ assimpTextureTypeToMEOV(type) };
                    const std::string id{ name.data, name.length };
                    cache[realType] = RESOURCES->LoadTexture(mLastLoadingDirectory / id, realType);
                }
            }
        }
        mCachedMaterials[i] = std::move(cache);
    }
}

}  // namespace meov::core::resources
