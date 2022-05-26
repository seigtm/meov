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
std::shared_ptr<shaders::Shader> Loader::LoadShader(const fs::path& path,
                                                    const shaders::ShaderType type) {
    if(type == shaders::ShaderType::Invalid || path.empty()) return nullptr;

    // Get shader sources in a string.
    std::ifstream ifs{ path };
    const std::string sources{ { std::istreambuf_iterator<char>{ ifs } }, std::istreambuf_iterator<char>{} };
    // Initialize shader with this sources.
    auto shader{ std::make_shared<shaders::Shader>() };
    shader->Initialize(type, sources);

    if(!shader->IsValid()) {
        return nullptr;
    }

    return shader;
}

std::shared_ptr<shaders::Program> Loader::LoadProgram(const fs::path& path) {
    if(path.empty() || !fs::exists(path.parent_path())) {
        LOGE << "The path '" << path.parent_path().c_str() << "' is empty or it doesn't exist.";
        return nullptr;
    }

    const auto name{ path.filename() };
    const auto root{ path.parent_path() };

    auto program{ std::make_shared<shaders::Program>() };
    program->Initialize(name.string());
    // Iterating through all files and directories in the 'root' directory.
    for(const auto& entry : fs::directory_iterator(root)) {
        // Skip if the entry is a directory (we obviously don't want to make a shader program from the directory).
        if(entry.is_directory()) continue;
        // Cast entry to fs::path.
        const fs::path entryPath{ entry };
        // Get the shader type from the file extension.
        const auto shaderType{ shaders::getTypeByExtention(entryPath.extension().string()) };
        // Load and attach the shader to the shader program.
        const auto wasShaderAttached{ program->Attach(LoadShader(entryPath, shaderType)) };
        if(!wasShaderAttached || !program->IsValid()) {
            LOGW << "Shader '" << entryPath.c_str() << "' wasn't attached! Shader program is invalid.";
            return nullptr;
        }
    }
    return program;
}

}  // namespace meov::core::resources
