#pragma once

#include "FrameBuffer.hpp"

namespace meov::core::gl {

class OpenGLFrameBuffer final : public FrameBuffer {
public:
    void Initialize(int32_t width, int32_t height) override;
    void Destroy() override;

    void Bind() override;
    void UnBind() override;

    uint32_t GetFrameTexture() override;
    uint32_t GetFrameDepthBuffer();

private:
    uint32_t mFBO{};
    uint32_t mRBO{};
    uint32_t mTexId{};
};

} // namespace meov::core::gl