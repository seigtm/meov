#pragma once

// STL.
#include <memory>
#include <filesystem>

// MEOV.
#include "shader.hpp"
#include "texture.hpp"

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

    virtual std::shared_ptr<Texture> LoadTexture(const fs::path& path, const Texture::Type type = Texture::Type::Diffuse);
    virtual std::shared_ptr<shaders::Shader> LoadShader(const fs::path& path,
                                                        const shaders::ShaderType type);
    virtual std::shared_ptr<shaders::Program> LoadProgram(const fs::path& path);
    virtual std::shared_ptr<Model> LoadModel(const fs::path& path) = 0;
};

}  // namespace meov::core::resources
