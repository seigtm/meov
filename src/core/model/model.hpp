#pragma once

// STL.
#include <memory>
#include <vector>

// MEOV.
#include "mesh.h"
#include "texture.hpp"
#include "graphics.hpp"

#include "Transformable.h"

namespace meov::core {

class Model : public mixin::Transformable {
public:
    explicit Model(std::vector<std::shared_ptr<core::Mesh>> &&meshes);

    void Draw(core::Graphics &g) const;

    const std::vector<std::shared_ptr<Mesh>> &GetMeshes() const;

private:
    std::vector<std::shared_ptr<core::Mesh>> mMeshes;
};

}  // namespace meov::core
