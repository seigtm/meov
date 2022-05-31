#include "common.hpp"

#include "texture.hpp"

namespace meov::core {

std::string Texture::Type2String(Type type) {
    switch(type) {
        case Type::Diffuse: return "diffuse";
        case Type::Specular: return "specular";
        case Type::Height: return "height";
        case Type::Normal: return "normal";
        case Type::Ambient: return "ambient";
        case Type::Cubemap: return "cubemap";
        case Type::Invalid: return "invalid";
        default: break;
    }
    return "invalid";
}

Texture::Texture()
    : resources::Resource{ "UNNAMED" }, mType{ Type::Invalid } {}

Texture::Texture(const unsigned char *bytes, int width, int height, int channels, Type type)
    : resources::Resource{ "UNNAMED" }, mType{ type } {
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
    mValid = true;
}

Texture::Texture(std::array<unsigned char *, 6> bytes, int width, int height, int channels)
    : resources::Resource{ "UNNAMED" }, mType{ Type::Cubemap } {
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mId);

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

    size_t counter{};
    for(auto *image : bytes) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + counter++, 0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    LOGD << "Skybox texture with id = " << mId << " was loaded.";
    mValid = true;
}

Texture::~Texture() {
    glDeleteTextures(1, &mId);
}

void Texture::Bind() {
    glBindTexture(mType == Type::Cubemap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, mId);
}

std::string Texture::Activate(const int id) {
    glActiveTexture(GL_TEXTURE0 + id);
    return Type2String(GetType());
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
