#include "assimp_loader.hpp"

namespace {

meov::core::Texture::Type assimpTextureTypeToMEOV(aiTextureType type) {
    using Type = meov::core::Texture::Type;
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

}  // anonymous namespace


namespace meov::core::resources {

std::shared_ptr<meov::core::Model> AssimpLoader::LoadModel(const fs::path &path) {
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

    std::vector<std::shared_ptr<Mesh>> meshes;
    for(size_t i{}; i < scene->mNumMeshes; ++i) {
        auto *asmesh{ scene->mMeshes[i] };
        if(auto mesh{ ProcessMesh(asmesh, scene) }; mesh) {
            mesh->Rename(std::string{ asmesh->mName.C_Str() });
            meshes.emplace_back(std::move(mesh));
        }
    }
    return std::make_shared<Model>(std::move(meshes));
}

std::shared_ptr<meov::core::Mesh> AssimpLoader::ProcessMesh(aiMesh *mesh, const aiScene *scene) const {
    std::vector<meov::core::Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);
    std::vector<unsigned> indices;

    for(unsigned i{}; i < mesh->mNumVertices; ++i) {
        // Get coordinates (aPos).
        glm::vec3 position{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        // Get color (aColor).
        glm::u8vec4 color{ 0xff, 0xff, 0xff, 0xff };
        if(mesh->mColors[0] != nullptr) {
            color = { mesh->mColors[0]->r * 255,
                      mesh->mColors[0]->g * 255,
                      mesh->mColors[0]->b * 255,
                      mesh->mColors[0]->a * 255 };
        }
        // Get texture coordinates (aTexPos).
        glm::vec2 texturePosition{ 0, 0 };
        // If mesh has texture coords.
        if(mesh->mTextureCoords[0]) {
            texturePosition.x = mesh->mTextureCoords[0][i].x;
            texturePosition.y = mesh->mTextureCoords[0][i].y;
        }
        vertices.emplace_back(std::move(position), std::move(color), std::move(texturePosition));
    }
    // Get indices from faces.
    for(unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for(unsigned j{}; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // Process materials.
    Material material{ mCachedMaterials.at(mesh->mMaterialIndex) };
    return std::make_shared<Mesh>(std::move(vertices), std::move(indices), std::move(material));
}

void AssimpLoader::PreLoadMaterials(aiMaterial **materials, size_t count) {
    static const std::array textureTypes{
        aiTextureType_DIFFUSE,
        aiTextureType_SPECULAR,
        aiTextureType_AMBIENT,
        aiTextureType_HEIGHT,
        aiTextureType_NORMALS
    };

    for(size_t i{}; i < count; ++i) {
        const aiMaterial *material{ materials[i] };
        Material cache;
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
