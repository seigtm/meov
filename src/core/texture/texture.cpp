#include "Common.hpp"

#include "texture.h"

namespace meov::core {

std::shared_ptr<Texture> Texture::Make(const std::string_view &path, const Type type) {
    return std::make_shared<Texture>(path, type);
}

Texture::Texture(const std::string_view &path, const Type type)
    : mPath{ path }
    , mType{ type } {
    if(path.empty()) {
        LOGW << "Creating texute with empty path parameter!";
        // stbi_load_from_memory()
        return;
    }

    int width, height, channels;
    auto bytes{ stbi_load(path.data(), &width, &height, &channels, 0) };
    if(nullptr == bytes) {
        LOGE << "Error while loading texture from '" << path << "'";
        LOGE << "    " << stbi_failure_reason();
        return;
    }
    glGenTextures(1, &mId);
    Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const GLenum format{ channels == 4 ? GL_RGBA : GL_RGB };

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(bytes);
    LOGD << "Texture " << path << " was loaded";
    mValid = true;
}

Texture::~Texture() {
    glDeleteTextures(1, &mId);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, mId);
}

void Texture::Activate(const int id) {
    glActiveTexture(GL_TEXTURE0 + id);
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
