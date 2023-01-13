#pragma once

#include <utils/types.hpp>
#include "core/resources/texture/texture.hpp"

namespace meov::core {

class Material {
public:
    Material();
    sptr<resources::Texture> &operator[](resources::Texture::Type type);
    const sptr<resources::Texture> operator[](resources::Texture::Type type) const;

    float GetShininess() const;
    void SetShininess(float value);

private:
    umap<resources::Texture::Type, sptr<resources::Texture>> mTextures;
    float mShininess{ 32.f };
};

}  // namespace meov::core
