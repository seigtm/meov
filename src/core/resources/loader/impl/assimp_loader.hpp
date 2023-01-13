#pragma once

// STL.
#include <array>
#include <memory>
#include <filesystem>
#include <set>
#include <string>

// MEOV.
#include "core/resources/loader/loader.hpp"
#include "core/model/model.hpp"
#include "core/resources/manager/resource_manager.hpp"
#include "core/mesh/vertex.hpp"
#include "core/material/material.hpp"

#include <utils/types.hpp>

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
    using TexturePtr = sptr<meov::core::resources::Texture>;
    using ModelPtr = sptr<meov::core::Model>;

public:
    AssimpLoader() = default;
    ~AssimpLoader() override = default;

    [[nodiscard]] sptr<meov::core::Model> LoadModel(const fs::path &path) override;

private:
    fs::path mLastLoadingDirectory;
    umap<u32, Material> mCachedMaterials;

    /*! \brief Mesh processing.
        \param[in] mesh Mesh to process.
        \param[in] scene aiScene object.
        \return Shared pointer to the processed mesh.
    */
    sptr<meov::core::Mesh> ProcessMesh(aiMesh *mesh, const aiScene *scene) const;

    void PreLoadMaterials(aiMaterial **materials, size_t count);
};

}  // namespace meov::core::resources
