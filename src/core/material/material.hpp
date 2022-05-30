#pragma once

#include <unordered_map>
#include <memory>
#include "texture.hpp"

namespace meov::core {

class Material {
public:
    Material();
    std::shared_ptr<Texture> &operator[](Texture::Type type);
    const std::shared_ptr<Texture> operator[](Texture::Type type) const;

    float GetShininess() const;
    void SetShininess(float value);

private:
    std::unordered_map<Texture::Type, std::shared_ptr<Texture>> mTextures;
    float mShininess{ 32.f };
};

}  // namespace meov::core
