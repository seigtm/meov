#include <common>

#include <utils/scope_wrapper/scope_wrapper.hpp>
#include <utils/stb/image.hpp>

#include "core/resources/image/image.hpp"
#include "core/resources/loader/loader.hpp"
#include "core/shaders/shaders_program/shaders_program.hpp"

namespace meov::core::resources {

sptr<Texture> Loader::LoadTexture(const fs::path& path, const Texture::Type type) {
    if(path.empty()) {
        LOGW << "Creating texture with empty path parameter!";
        return nullptr;
    }

    if(utils::stb::image image{ path.string() }; image.wasLoaded) {
        return std::make_shared<Texture>(image, type);
    }

    LOGE << "Error while loading texture from '" << path.string() << "'";
    LOGE << "    " << stbi_failure_reason();
    return nullptr;
}

sptr<Texture> Loader::LoadSkybox(const fs::path& path) {
    if(path.empty()) {
        LOGW << "Creating skybox texture with empty path parameter!";
        return nullptr;
    }

    // Vector of correctly named faces files.
    static constexpr std::array faces{
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };
    // Disabling vertical flip to get textures right.

    const utils::ScopeWrapper stbiFlipVerticallyWrapper([] {
        stbi_set_flip_vertically_on_load(false);
    }, [] {
        stbi_set_flip_vertically_on_load(true);
    });

    // Array of bytes.
    constexpr size_t ImagesCount{ 6 };
    using STBImageArray = std::array<utils::stb::image, ImagesCount>;
    STBImageArray images;
    // Load every face.
    const std::string pathForLog{ path.string() };
    STBImageArray::size_type counter{};
    for(const auto &face : faces) {
        utils::stb::image image{ (path / face).string() };
        if(!image.wasLoaded) {
            LOGE << "Error while loading texture "
                 << "'" << face << "'"
                 << " from '" << path.string() << "'";
            LOGE << "    " << stbi_failure_reason();
            return nullptr;
        }
        if(counter > 0 && images.front() != image) {
            constexpr std::string_view errmsg{
                "Can't load skybox because its images don't have"
                " the same size and number of channels."
            };
            LOGE << errmsg.data() << " Path: " << pathForLog.c_str();
            throw std::invalid_argument{ std::string{ errmsg } };
        }
        images.at(counter) = std::move(image);
        ++counter;
    }

    LOGD << "Skybox texture '" << pathForLog.c_str() << "' was loaded!";
    return std::make_shared<Texture>(images);
}

sptr<shaders::Shader> Loader::LoadShader(const fs::path& path, const shaders::ShaderType type) {
    if(type == shaders::ShaderType::Invalid || path.empty()) {
        return nullptr;
    }

    std::ifstream ifs{ path };
    const std::string sources{ { std::istreambuf_iterator<char>{ ifs } }, std::istreambuf_iterator<char>{} };

    auto shader{ std::make_shared<shaders::Shader>() };
    shader->Initialize(type, sources);
    return shader;
}

sptr<shaders::Program> Loader::LoadProgram(const fs::path& path) {
    if(path.empty()) return nullptr;

    const auto name{ path.filename() };
    const auto root{ path.parent_path() };
    if(!fs::exists(root))
        return nullptr;

    auto program{ std::make_shared<shaders::Program>(name.string()) };
    program->SetPath(path);
    program->Initialize();
    for(const auto& entry : fs::directory_iterator(root)) {
        const fs::path entryPath{ entry };
        program->Attach(
            LoadShader(entryPath, shaders::getTypeByExtention(entryPath.extension().string())));
    }
    return program;
}

}  // namespace meov::core::resources
