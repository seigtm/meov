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
#include "vertex.hpp"
#include "material.hpp"

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

class AssimpLoader final : public Loader {
    using TexturePtr = std::shared_ptr<meov::core::Texture>;
    using ModelPtr = std::shared_ptr<meov::core::Model>;

public:
    AssimpLoader() = default;
    ~AssimpLoader() override = default;

    std::shared_ptr<meov::core::Model> LoadModel(const fs::path &path) override;

private:
    fs::path mLastLoadingDirectory;

    /*! \brief Recursive nodes processing.
        \param[in] node Parent node to process.
        \param[in] scene aiScene object.
        \return Vector of shared pointers to the scene's meshes.
    */
    std::vector<std::shared_ptr<meov::core::Mesh>> ProcessNode(aiNode *node, const aiScene *scene) const;

    /*! \brief Mesh processing.
        \param[in] mesh Mesh to process.
        \param[in] scene aiScene object.
        \return Shared pointer to the processed mesh.
    */
    std::shared_ptr<meov::core::Mesh> ProcessMesh(aiMesh *mesh, const aiScene *scene) const;

    /*! \brief Material processing.
        Loads given material - `mat`.
        \param[in] mat Assimp material object to get textures from.
        \return Material
    */
    Material LoadMaterial(aiMaterial *mat) const;
};

}  // namespace meov::core::resources
