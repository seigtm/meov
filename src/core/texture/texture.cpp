#include "common.hpp"

#include "texture.hpp"

namespace meov::core {

Texture::Texture()
    : mType{ Type::Invalid } {}

Texture::Texture(const unsigned char *bytes, int width, int height, int channels, Type type)
    : mType{ type } {
    glGenTextures(1, &mId);
    Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format;
    switch(channels) {
        case 1: format = GL_RED; break;
        case 2: format = GL_RG; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default:
            LOGE << "stb_image library returned invalid channels number = " << channels;
            return;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    LOGD << "Texture was loaded";
    mValid = true;
}

Texture::Texture(std::array<unsigned char *, 6> bytes, int width, int height, int channels)
    : mType{ Type::Cubemap } {
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mId);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    GLenum format;
    switch(channels) {
        case 1: format = GL_RED; break;
        case 2: format = GL_RG; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default:
            LOGE << "stb_image library returned invalid channels number = " << channels;
            return;
    }

    for(unsigned i{}; i < bytes.size(); ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes.at(i));
    }

    LOGD << "Skybox texture with id = " << mId << " was loaded.";
    mValid = true;
}

Texture::~Texture() {
    glDeleteTextures(1, &mId);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, mId);
}

std::string Texture::Activate(const int id) {
    glActiveTexture(GL_TEXTURE0 + id);
    switch(GetType()) {
        case Texture::Type::Diffuse:
            return "textureDiffuse";
        case Texture::Type::Specular:
            return "textureSpecular";
        case Texture::Type::Normal:
            return "textureNormal";
        case Texture::Type::Height:
            return "textureHeight";
        default: break;
    }
    return "invalid texture";
}

bool Texture::Valid() const {
    return mValid;
}

unsigned Texture::GetID() const {
    return mId;
}

Texture::Type Texture::GetType() const {
    return mType;
}

}  // namespace meov::core
