#pragma once

// STL.
#include <array>
#include <memory>
#include <filesystem>
#include <set>
#include <string>

// MEOV.
#include "loader.hpp"
#include "model.hpp"
#include "resource_manager.hpp"
#include "vertex.h"

// Logger.
#include <plog/Log.h>

// GLM.
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Assimp API.
#include <assimp/Importer.hpp>   // C++ importer interface.
#include <assimp/scene.h>        // Output data structure.
#include <assimp/postprocess.h>  // Post processing flags.

namespace meov::core::resources {

class AssimpLoader : public Loader {
    using TexturePtr = std::shared_ptr<meov::core::Texture>;
    using ModelPtr = std::shared_ptr<meov::core::Model>;

public:
    AssimpLoader() = default;
    ~AssimpLoader() = default;

    std::shared_ptr<meov::core::Model> LoadModel(const fs::path &path) override;

private:
    /*! \brief Recursive nodes processing.
        \param[in] node Parent node to process.
        \param[in] scene aiScene object.
        \return Vector of shared pointers to the scene's meshes.
    */
    std::vector<std::shared_ptr<meov::core::Mesh>> ProcessNode(aiNode *node, const aiScene *scene);

    /*! \brief Mesh processing.
        \param[in] mesh Mesh to process.
        \param[in] scene aiScene object.
        \return Shared pointer to the processed mesh.
    */
    std::shared_ptr<meov::core::Mesh> ProcessMesh(aiMesh *mesh, const aiScene *scene);

    /*! \brief Material processing.
        Loads all textures from given material - `mat`.
        \param[in] mat Assimp material object to get textures from.
        \return Vector of shared pointers to the loaded textures from the material.
    */
    std::vector<std::shared_ptr<meov::core::Texture>> LoadMaterialTextures(aiMaterial *mat);

    // Temporary model object to return with LoadModel() method.
    std::shared_ptr<meov::core::Model> mModel;
};

}  // namespace meov::core::resources
