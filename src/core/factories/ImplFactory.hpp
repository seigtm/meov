#pragma once

#include "ShadersProgram.hpp"
#include "Graphics.hpp"

namespace meov::core::factories {

class ImplFactory {
public:
    static ImplFactory *Instance();

    virtual std::shared_ptr<shaders::Shader::Impl> MakeShaderImpl(
        shaders::ShaderType type,
        const std::string_view &source = "") = 0;

    virtual std::shared_ptr<shaders::Program::Impl> MakeProgramImpl(
        const std::string &name) = 0;

    virtual std::shared_ptr<Graphics::Impl> MakeGraphicsImpl() = 0;
};


}  // namespace meov::core::factories