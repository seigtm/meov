#include "core/material/material.hpp"

namespace meov::core {

Material::Material()
    : mTextures{
        { resources::Texture::Type::Diffuse, nullptr },
        { resources::Texture::Type::Specular, nullptr },
        { resources::Texture::Type::Height, nullptr },
        { resources::Texture::Type::Normal, nullptr },
        { resources::Texture::Type::Ambient, nullptr },
        { resources::Texture::Type::Cubemap, nullptr },
        { resources::Texture::Type::Invalid, nullptr },
    } {}

sptr<resources::Texture> &Material::operator[](resources::Texture::Type type) {
    return mTextures[type];
}
const sptr<resources::Texture> Material::operator[](resources::Texture::Type type) const {
    return mTextures.at(type);
}

float Material::GetShininess() const {
    return mShininess;
}
void Material::SetShininess(float value) {
    mShininess = value;
}


}  // namespace meov::core
