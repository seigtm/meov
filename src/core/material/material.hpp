#pragma once

#include <memory>

namespace meov::core {

class Texture;

class Material {
public:
    std::shared_ptr<Texture> mDiffuse;
    std::shared_ptr<Texture> mSpecular;
    float mShininess{ 32.f };
};

}  // namespace meov::core
