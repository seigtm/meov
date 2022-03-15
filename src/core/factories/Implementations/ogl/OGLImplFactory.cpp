#include "Common.hpp"

#include "OGLShader.hpp"
#include "OGLShadersProgram.hpp"

#include "OGLImplFactory.hpp"


namespace meov::core::factories {

std::shared_ptr<shaders::Shader::Impl> OGLImplFactory::MakeShaderImpl(
    shaders::ShaderType type, const std::string_view &source) {
    return std::make_shared<shaders::gl::OGLShaderImpl>(type, source);
}

std::shared_ptr<shaders::Program::Impl> OGLImplFactory::MakeProgramImpl(const std::string &name) {
    return std::make_shared<shaders::gl::OGLProgramImpl>(name);
}

} // namespace meov::core::factories
