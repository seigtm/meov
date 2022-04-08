#include "assimp_loader.hpp"

namespace meov::core::resources {

std::shared_ptr<meov::core::Model> AssimpLoader::LoadModel(const fs::path &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOGE << importer.GetErrorString();
        return nullptr;
    }
    if(!scene->mNumMeshes) {
        LOGI << "No meshes in model. Breaking load process.";
        return nullptr;
    }
    mLastLoadingDirectory = path.parent_path();
    return std::make_shared<Model>(ProcessNode(scene->mRootNode, scene));
}

std::vector<std::shared_ptr<meov::core::Mesh>> AssimpLoader::ProcessNode(aiNode *node, const aiScene *scene) const {
    std::vector<std::shared_ptr<Mesh>> meshes;
    meshes.reserve(node->mNumMeshes);
    for(size_t currentMeshIndex{}; currentMeshIndex < node->mNumMeshes; ++currentMeshIndex) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[currentMeshIndex]];
        meshes.emplace_back(ProcessMesh(mesh, scene));
        LOGI << "       Mesh processed!";
    }

    for(size_t currentChildIndex{}; currentChildIndex < node->mNumChildren; currentChildIndex++) {
        const auto processedMeshes{ ProcessNode(node->mChildren[currentChildIndex], scene) };
        meshes.insert(meshes.end(), processedMeshes.begin(), processedMeshes.end());
    }
    return meshes;
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
    return std::make_shared<meov::core::Mesh>(
        std::move(vertices),
        std::move(indices),
        LoadMaterialTextures(scene->mMaterials[mesh->mMaterialIndex]));
}

std::vector<std::shared_ptr<Texture>> AssimpLoader::LoadMaterialTextures(aiMaterial *mat) const {
    const std::array textureTypes{ aiTextureType_DIFFUSE,
                                   aiTextureType_SPECULAR,
                                   aiTextureType_AMBIENT,
                                   aiTextureType_HEIGHT,
                                   aiTextureType_NORMALS };

    const std::unordered_map<aiTextureType, Texture::Type> typeConv{
        { aiTextureType_DIFFUSE, Texture::Type::Diffuse },
        { aiTextureType_SPECULAR, Texture::Type::Specular },
        { aiTextureType_HEIGHT, Texture::Type::Height },
        { aiTextureType_NORMALS, Texture::Type::Normal },
        { aiTextureType_AMBIENT, Texture::Type::Invalid }
    };

    const auto ExtractTexturesNamesByType{
        [&](aiTextureType type) {
            const auto count{ mat->GetTextureCount(type) };
            std::set<std::string> names;
            for(unsigned current{}; current < count; ++current) {
                aiString str;
                mat->GetTexture(type, current, &str);
                names.emplace((mLastLoadingDirectory / str.C_Str()).string());
            }
            return std::move(names);
        }
    };

    std::vector<std::shared_ptr<Texture>> textures;

    for(const auto type : textureTypes) {
        const auto names{ ExtractTexturesNamesByType(type) };
        std::transform(
            names.begin(), names.end(),
            std::back_inserter(textures),
            [convertedType = typeConv.at(type)] (const auto &name) {
                return RESOURCES->LoadTexture(name, convertedType);
            });
    }

    return textures;
}

}  // namespace meov::core::resources
