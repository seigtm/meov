#pragma once

// STL.
#include <filesystem>
#include <memory>
#include <vector>

// MEOV.
#include "core/shaders/shader/shader.hpp"
#include "core/resources/texture/texture.hpp"

namespace fs = std::filesystem;

namespace meov::core {

class Texture;
class Mesh;
class Model;

namespace shaders {
class Program;
class Setter;
}  // namespace shaders

}  // namespace meov::core

namespace meov::core::resources {

class Loader {
public:
    virtual ~Loader() = default;

    [[nodiscard]] virtual sptr<Texture> LoadTexture(const fs::path& path,
        const Texture::Type type = Texture::Type::Invalid);
    [[nodiscard]] virtual sptr<Texture> LoadSkybox(const fs::path& path);
    [[nodiscard]] virtual sptr<shaders::Shader> LoadShader(const fs::path& path,
        const shaders::ShaderType type);
    [[nodiscard]] virtual sptr<shaders::Program> LoadProgram(const fs::path& path);
    [[nodiscard]] virtual sptr<Model> LoadModel(const fs::path& path) = 0;
};

}  // namespace meov::core::resources
