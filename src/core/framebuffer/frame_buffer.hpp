#pragma once

#include <cstdint>
#include <memory>

namespace meov::core {

class FrameBuffer final {
public:
    static constexpr int32_t DefaultWidth{ 1280 };
    static constexpr int32_t DefaultHeight{ 760 };

    class Impl {
    public:
        Impl(int32_t width, int32_t height);
        virtual ~Impl() = default;
        virtual void Bind(){};
        virtual void UnBind(){};
        virtual uint32_t GetFrameTexture() const = 0;

        int32_t Width() const;
        int32_t Height() const;

    protected:
        int32_t mWidth{ -1 };
        int32_t mHeight{ -1 };
    };

    FrameBuffer(int32_t width = DefaultWidth, int32_t height = DefaultHeight);

    void Bind();
    void UnBind();
    uint32_t GetFrameTexture() const;

    int32_t Width() const;
    int32_t Height() const;

protected:
    std::shared_ptr<Impl> mImpl;
};

};  // namespace meov::core
