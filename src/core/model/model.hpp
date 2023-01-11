#pragma once

// STL.
#include <memory>
#include <vector>

// MEOV.
#include "core/mesh/mesh.hpp"
#include "core/texture/texture.hpp"
#include "core/graphics/graphics.hpp"
#include "core/resources/manager/resource.hpp"

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
