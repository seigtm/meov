#pragma once

// STL.
#include <memory>
#include <vector>

// MEOV.
#include "mesh.hpp"
#include "texture.hpp"
#include "graphics.hpp"
#include "resource.hpp"

namespace meov::core {

class Model : public resources::Resource {
public:
    explicit Model(std::vector<std::shared_ptr<core::Mesh>> &&meshes);

    void Draw(core::Graphics &g) const;

    const std::vector<std::shared_ptr<Mesh>> &GetMeshes() const;

private:
    std::vector<std::shared_ptr<core::Mesh>> mMeshes;
};

}  // namespace meov::core
