#pragma once

#include "FrameBuffer.hpp"

namespace meov::core::gl {

class FrameBufferImplementation final {
    friend class FrameBuffer<FrameBufferImplementation>;

    FrameBufferImplementation(int32_t width, int32_t height);
public:
    ~FrameBufferImplementation();

    void Bind();
    void UnBind();

    uint32_t GetFrameTexture();
    uint32_t GetFrameDepthBuffer();

private:
    uint32_t mFBO{};
    uint32_t mRBO{};
    uint32_t mTexId{};
    int32_t mWidth{ -1 };
    int32_t mHeight{ -1 };
};

using FrameBuffer = meov::core::FrameBuffer<FrameBufferImplementation>;

} // namespace meov::core::gl