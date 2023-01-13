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

    virtual [[nodiscard]] sptr<Texture> LoadTexture(const fs::path& path,
        const Texture::Type type = Texture::Type::Invalid);
    virtual [[nodiscard]] sptr<Texture> LoadSkybox(const fs::path& path);
    virtual [[nodiscard]] sptr<shaders::Shader> LoadShader(const fs::path& path,
        const shaders::ShaderType type);
    virtual [[nodiscard]] sptr<shaders::Program> LoadProgram(const fs::path& path);
    virtual [[nodiscard]] sptr<Model> LoadModel(const fs::path& path) = 0;
};

}  // namespace meov::core::resources
