#pragma once

// STL.
#include <memory>
#include <vector>

// MEOV.
#include "mesh.h"
#include "texture.h"
#include "Graphics.hpp"

namespace meov::core {

class Model {
public:
    Model(std::vector<std::shared_ptr<core::Mesh>> &&meshes);

    void Draw(core::Graphics &g) const;

private:
    std::vector<std::shared_ptr<core::Mesh>> mMeshes;
};

}  // namespace meov::core
