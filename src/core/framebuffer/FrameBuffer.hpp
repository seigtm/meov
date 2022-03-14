#pragma once

#include <cstdint>
#include <memory>

namespace meov::core {

constexpr int32_t DefaultFrameBufferWidth{ 1280 };
constexpr int32_t DefaultFrameBufferHeight{ 760 };

template<class Implementation>
class FrameBuffer final {
public:
    void Initialize(
        int32_t width = DefaultFrameBufferWidth,
        int32_t height = DefaultFrameBufferHeight) {
        mImpl.reset(new Implementation{ width, height });
    }
    void Destroy() {
        mImpl.reset();
    }

    void Bind() {
        if (IsInitialized()) mImpl->Bind();
    }
    void UnBind() {
        if (IsInitialized()) mImpl->UnBind();
    }

    uint32_t GetFrameTexture() const {
        if (IsInitialized()) {
            return mImpl->GetFrameTexture();
        }
        return 0;
    };

    bool IsInitialized() const { return mImpl != nullptr; }

protected:
    std::unique_ptr<Implementation> mImpl;
};

};  // namespace meov::core
