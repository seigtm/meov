#pragma once

#include <cstdint>

namespace meov::core {

class FrameBuffer {
public:
    virtual ~FrameBuffer() = default;
    virtual void Initialize(int32_t width, int32_t height) = 0;
    virtual void Destroy() = 0;

    virtual void Bind() = 0;
    virtual void UnBind() = 0;

    virtual uint32_t GetFrameTexture() = 0;

    bool IsInitialized() const { return mInitialized; }

protected:
    int32_t mWidth{ -1 };
    int32_t mHeight{ -1 };
    bool mInitialized{ false };
};

};  // namespace meov::core
