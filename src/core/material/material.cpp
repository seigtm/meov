#include "core/material/material.hpp"

namespace meov::core {

Material::Material()
    : mTextures{
        { Texture::Type::Diffuse, nullptr },
        { Texture::Type::Specular, nullptr },
        { Texture::Type::Height, nullptr },
        { Texture::Type::Normal, nullptr },
        { Texture::Type::Ambient, nullptr },
        { Texture::Type::Cubemap, nullptr },
        { Texture::Type::Invalid, nullptr },
    } {}

std::shared_ptr<Texture>&
Material::operator[](Texture::Type type) {
    return mTextures[type];
}
const std::shared_ptr<Texture> Material::operator[](Texture::Type type) const {
    return mTextures.at(type);
}

float Material::GetShininess() const {
    return mShininess;
}
void Material::SetShininess(float value) {
    mShininess = value;
}


}  // namespace meov::core
