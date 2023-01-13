#pragma once

#include "core/framebuffer/frame_buffer.hpp"

namespace meov::core::gl {

class OGLFrameBufferImpl final : public FrameBuffer::Impl {
public:
    OGLFrameBufferImpl(i32 width, i32 height);
    ~OGLFrameBufferImpl();

    void Bind() override;
    void UnBind() override;

    u32 GetFrameTexture() const override;
    u32 GetFrameDepthBuffer() const;

private:
    u32 mFBO{};
    u32 mRBO{};
    u32 mTexId{};
};

}  // namespace meov::core::gl
