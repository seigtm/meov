#pragma once

#include "impl_factory.hpp"

namespace meov::core::factories {

class OGLImplFactory : public ImplFactory {
public:
    std::shared_ptr<shaders::Shader::Impl> MakeShaderImpl(
        shaders::ShaderType type,
        const std::string_view &source = "") override;
    std::shared_ptr<shaders::Program::Impl> MakeProgramImpl(
        const std::string &name) override;
    std::shared_ptr<Graphics::Impl> MakeGraphicsImpl() override;
};

}  // namespace meov::core::factories
