#include "common.hpp"

#include "loader.hpp"
#include "shaders_program.hpp"

namespace meov::core::resources {

std::shared_ptr<Texture> Loader::LoadTexture(const fs::path& path, const Texture::Type type) {
    if(path.empty()) {
        LOGW << "Creating texture with empty path parameter!";
        return nullptr;
    }

    int width, height, channels;
    auto bytes{ stbi_load(path.string().c_str(), &width, &height, &channels, 0) };
    if(nullptr == bytes) {
        LOGE << "Error while loading texture from '" << path.string() << "'";
        LOGE << "    " << stbi_failure_reason();
        return nullptr;
    }

    auto texture{ std::make_shared<meov::core::Texture>(bytes, width, height, channels, type) };

    stbi_image_free(bytes);

    return texture;
}

std::shared_ptr<Texture> Loader::LoadSkybox(const fs::path& path) {
    if(path.empty()) {
        LOGW << "Creating skybox texture with empty path parameter!";
        return nullptr;
    }

    int width, height, channels;
    // Vector of correctly named faces files.
    const std::vector<std::string> faces{
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };
    // Disabling vertical flip to get textures right.
    stbi_set_flip_vertically_on_load(false);
    // Array of bytes.
    std::array<unsigned char*, 6> bytes;
    // Load every face.
    int previousWidth{};
    int previousHeight{};
    int previousChannels{};
    for(unsigned i{}; i < bytes.size(); ++i) {
        const auto filename{ path / faces.at(i) };
        bytes[i] = stbi_load(filename.string().c_str(), &width, &height, &channels, 0);
        // Check that all images have the same width, height and number of channels.
        if(i == 0) {
            previousWidth = width;
            previousHeight = height;
            previousChannels = channels;
        } else if(previousWidth != width || previousHeight != height || previousChannels != channels) {
            constexpr std::string_view errmsg{
                "Can't load skybox because its images don't have"
                " the same size and number of channels."
            };
            LOGE << errmsg << " Path: " << path.c_str();
            stbi_set_flip_vertically_on_load(true);
            throw std::invalid_argument{ std::string{ errmsg } };
        }
        if(nullptr == bytes[i]) {
            LOGE << "Error while loading texture "
                 << "'" << faces.at(i) << "'"
                 << " from '" << path.string() << "'";
            LOGE << "    " << stbi_failure_reason();
            stbi_set_flip_vertically_on_load(true);
            return nullptr;  // FIXME: Don't return just now. You should clean the memory from previous loaded images.
        }
    }
    // Create texture with array<bytes> c-tor.
    auto texture{ std::make_shared<meov::core::Texture>(std::move(bytes), width, height, channels) };  // FIXME: We hope that every cubemap image has the same width, height and channels.
    // Clean-up in the end.
    for(auto&& b : bytes) {
        stbi_image_free(b);
    }
    LOGD << "Skybox texture '" << path.c_str() << "' was loaded!";
    // Return flip back to normal.
    stbi_set_flip_vertically_on_load(true);
    // Return texture object.
    return texture;
}

std::shared_ptr<shaders::Shader> Loader::LoadShader(const fs::path& path,
                                                    const shaders::ShaderType type) {
    if(type == shaders::ShaderType::Invalid || path.empty()) {
        return nullptr;
    }

    std::ifstream ifs{ path };
    const std::string sources{ { std::istreambuf_iterator<char>{ ifs } }, std::istreambuf_iterator<char>{} };

    auto shader{ std::make_shared<shaders::Shader>() };
    shader->Initialize(type, sources);
    return shader;
}

std::shared_ptr<shaders::Program> Loader::LoadProgram(const fs::path& path) {
    if(path.empty()) return nullptr;

    const auto name{ path.filename() };
    const auto root{ path.parent_path() };
    if(!fs::exists(root))
        return nullptr;

    auto program{ std::make_shared<shaders::Program>() };
    program->Initialize(name.string());
    for(const auto& entry : fs::directory_iterator(root)) {
        const fs::path entryPath{ entry };
        program->Attach(
            LoadShader(entryPath, shaders::getTypeByExtention(entryPath.extension().string())));
    }
    return program;
}

}  // namespace meov::core::resources
