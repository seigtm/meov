#include "common.hpp"

#include "ogl_shader.hpp"
#include "ogl_shaders_program.hpp"
#include "ogl_graphics.hpp"
#include "ogl_frame_buffer.hpp"

#include "ogl_impl_factory.hpp"


namespace meov::core::factories {

std::shared_ptr<shaders::Shader::Impl> OGLImplFactory::MakeShaderImpl(
    shaders::ShaderType type, const std::string_view &source) {
    return std::make_shared<shaders::gl::OGLShaderImpl>(type, source);
}

std::shared_ptr<shaders::Program::Impl> OGLImplFactory::MakeProgramImpl(const std::string &name) {
    return std::make_shared<shaders::gl::OGLProgramImpl>(name);
}

std::shared_ptr<Graphics::Impl> OGLImplFactory::MakeGraphicsImpl() {
    return std::make_shared<gl::OGLGraphicsImpl>();
}

std::shared_ptr<FrameBuffer::Impl> OGLImplFactory::MakeFrameBufferImpl(int32_t width, int32_t height) {
    return std::make_shared<gl::OGLFrameBufferImpl>(width, height);
}

}  // namespace meov::core::factories
