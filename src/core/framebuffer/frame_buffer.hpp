#pragma once

#include <utils/types.hpp>

namespace meov::core {

class FrameBuffer final {
public:
    static constexpr i32 DefaultWidth{ 1280 };
    static constexpr i32 DefaultHeight{ 760 };

    class Impl {
    public:
        Impl(i32 width, i32 height);
        virtual ~Impl() = default;
        virtual void Bind(){};
        virtual void UnBind(){};
        virtual u32 GetFrameTexture() const = 0;

        i32 Width() const;
        i32 Height() const;

    protected:
        i32 mWidth{ -1 };
        i32 mHeight{ -1 };
    };

    FrameBuffer(i32 width = DefaultWidth, i32 height = DefaultHeight);

    void Bind();
    void UnBind();
    u32 GetFrameTexture() const;

    i32 Width() const;
    i32 Height() const;

private:
    sptr<Impl> mImpl;
};

};  // namespace meov::core
