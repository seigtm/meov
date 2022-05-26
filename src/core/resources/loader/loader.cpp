#include "common.hpp"

#include "loader.hpp"
#include "shaders_program.hpp"

namespace meov::core::resources {

std::shared_ptr<Texture> Loader::LoadTexture(const fs::path& path, const Texture::Type type) {
    if(path.empty()) {
        LOGW << "Creating texute with empty path parameter!";
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
std::shared_ptr<shaders::Shader> Loader::LoadShader(const fs::path& path,
                                                    const shaders::ShaderType type) {
    if(type == shaders::ShaderType::Invalid || path.empty()) {
        return nullptr;
    }

    std::ifstream ifs{ path };
    const std::string sources{ { std::istreambuf_iterator<char>{ ifs } }, std::istreambuf_iterator<char>{} };

    // NEW REALIZATION:
    auto shader{ std::make_shared<shaders::Shader>() };
    shader->Initialize(type, sources);
    return shader;

    // OLD: (Shader has no contructor which takes Type and std::string).
    // return std::make_shared<shaders::Shader>(type, sources);
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
