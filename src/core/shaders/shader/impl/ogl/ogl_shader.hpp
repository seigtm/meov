#pragma once

#include <memory>
#include <string>

#include "shader.hpp"

namespace meov::core::shaders::gl {

std::string getDefaultShaderSource(ShaderType type);

class OGLShaderImpl final : public Shader::Impl {
public:
    explicit OGLShaderImpl(ShaderType type, const std::string_view &source = "");
    ~OGLShaderImpl() override;

    bool IsValid() const override;
    static GLenum GetOriginalType(ShaderType type);

private:
    bool mValid{ false };
};

}  // namespace meov::core::shaders::gl
