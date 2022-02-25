#include "Common.hpp"

#include "texture.h"

namespace meov::core {

Texture::Texture(const std::string &path)
    : mValid{ false } {
    if(path.empty()) {
        // stbi_load_from_memory()
        return;
    }

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    auto img{ stbi_load(path.c_str(), &width, &height, &channels, 0) };
    if(nullptr == img) {
        LOGE << "[Texture] Error while loading texture from '" << path << "'";
        LOGE << "[Texture]     " << stbi_failure_reason();
        return;
    }
    glGenTextures(1, &mId);
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(img);
    mValid = true;
}

Texture::~Texture() {
    glDeleteTextures(1, &mId);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, mId);
}

bool Texture::valid() const {
    return mValid;
}

unsigned Texture::getID() const {
    return mId;
}

} // namespace meov::core