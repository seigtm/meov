#include <common>

#include <utils/stb/image.hpp>

#include "core/resources/texture/texture.hpp"
#include "core/resources/image/image.hpp"

namespace meov::core::resources {

namespace {
[[nodiscard]] static constexpr GLenum formatFrom(const i32 channels) {
    switch(channels) {
        case 1: return GL_RED;
        case 2: return GL_RG;
        case 3: return GL_RGB;
        case 4: return GL_RGBA;
        default: return GL_NONE;
    }
}
}

std::string_view Texture::Type2String(Type type) noexcept {
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

Texture::Texture(const std::span<byte> bytes, i32 width, i32 height, i32 channels, Type type)
    : Resource{ std::string{ "texture" } }, mType{ type } {
    MakeFrom(bytes, width, height, channels);
    AppendIDToName();
}

Texture::Texture(const Image &image, Type type)
    : Resource{ image.Name(), image.GetPath() }, mType{ type } {
    MakeFrom(image.raw(), image.size().x, image.size().y, image.channels());
    AppendIDToName();
}

Texture::Texture(const utils::stb::image &image, Type type)
    : Resource{ fs::path{ image.filename } }, mType{ type } {
    MakeFrom(image.raw(), image.width, image.height, image.channels);
    AppendIDToName();
}

Texture::Texture(const std::array<std::span<byte>, CubeMapImageCount> &bytes, i32 width, i32 height, i32 channels)
    : Resource{ std::string{ "skybox" } }, mType{ Type::Cubemap } {
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mId);

    const GLenum format{ formatFrom(channels) };
    if (format == GL_NONE) {
        LOGE << "Invalid channels number: " << channels;
        return;
    }

    size_t counter{};
    for(const auto &image : bytes) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + counter++, 0, format, width, height, 0,
            GL_RGB, GL_UNSIGNED_BYTE, image.data());
    }

    SetupCubeMapParams();
    LOGD << "Cubemap texture with id = " << mId << " was loaded.";
    mValid = true;

    AppendIDToName();
}

Texture::Texture(const std::array<Image, CubeMapImageCount> &images)
    : Resource{ images.front().Name(), images.front().GetPath() }, mType{ Type::Cubemap } {
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mId);

    const auto size{ images.front().size() };

    size_t counter{};
    for(const auto &image : images) {
        if (size != image.size()) {
            LOGE << "Cannot create Cubemap texture from textures with different width and height";
            glDeleteTextures(1, &mId);
            return;
        }

        const GLenum format{ formatFrom(image.channels()) };
        if (format == GL_NONE) {
            LOGE << "Invalid channels: " << image.channels();
            return;
        }

        const auto width{ image.size().x };
        const auto height{ image.size().y };
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + counter++, 0, format, width, height, 0,
            GL_RGB, GL_UNSIGNED_BYTE, image.raw().data());
    }

    SetupCubeMapParams();
    LOGD << "Cubemap texture with id = " << mId << " was loaded.";
    mValid = true;

    AppendIDToName();
}

Texture::Texture(const std::array<utils::stb::image, CubeMapImageCount> &images)
    : Resource{ fs::path(images.front().filename) }, mType{ Type::Cubemap } {
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mId);

    const auto &first{ images.front() };

    size_t counter{};
    for(const auto &image : images) {
        if (first != image) {
            LOGE << "Cannot create Cubemap texture from textures with different width and height";
            glDeleteTextures(1, &mId);
            return;
        }

        const GLenum format{ formatFrom(image.channels) };
        if (format == GL_NONE) {
            LOGE << "Invalid channels: " << image.channels;
            return;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + counter++, 0, format,
            image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.bytes);
    }

    SetupCubeMapParams();
    LOGD << "Cubemap texture with id = " << mId << " was loaded.";
    mValid = true;

    AppendIDToName();
}


Texture::~Texture() {
    glDeleteTextures(1, &mId);
}

void Texture::Bind() {
    glBindTexture(mType == Type::Cubemap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, mId);
}

std::string Texture::Activate(const i32 id) {
    glActiveTexture(GL_TEXTURE0 + id);
    return std::string{ Type2String(GetType()) };
}

bool Texture::Valid() const {
    return mValid;
}

u32 Texture::GetID() const {
    return mId;
}

Texture::Type Texture::GetType() const {
    return mType;
}

void Texture::MakeFrom(const std::span<const byte> bytes, const u32 width, const u32 height,
    const i32 channels) {
    glGenTextures(1, &mId);
    Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (const auto format{ formatFrom(channels) }; format != GL_NONE) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes.data());
        glGenerateMipmap(GL_TEXTURE_2D);
        mValid = true;
        return;
    }
    LOGE << "Invalid channels number: " << channels;
}

void Texture::SetupCubeMapParams() {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Texture::AppendIDToName() {
    if (mValid) {
        Rename(Name() + std::to_string(mId));
    }
}

}  // namespace meov::core::resources
