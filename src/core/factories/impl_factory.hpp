#pragma once

#include "core/shaders/shaders_program/shaders_program.hpp"
#include "core/graphics/graphics.hpp"
#include "core/framebuffer/frame_buffer.hpp"

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

    virtual std::shared_ptr<FrameBuffer::Impl> MakeFrameBufferImpl(
        int32_t width, int32_t height) = 0;
};

}  // namespace meov::core::factories
