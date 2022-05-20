#pragma once

#include "frame_buffer.hpp"

namespace meov::core::gl {

class OGLFrameBufferImpl final : public FrameBuffer::Impl {
public:
    OGLFrameBufferImpl(int32_t width, int32_t height);
    ~OGLFrameBufferImpl();

    void Bind() override;
    void UnBind() override;

    uint32_t GetFrameTexture() const override;
    uint32_t GetFrameDepthBuffer() const;

private:
    uint32_t mFBO{};
    uint32_t mRBO{};
    uint32_t mTexId{};
};

}  // namespace meov::core::gl
