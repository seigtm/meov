#include <cstdint>

namespace meov::core {

class FrameBuffer {
public:
    FrameBuffer()
        : mFBO{ 0 }, mDepthId{ 0 } {}

    virtual void create_buffers(int32_t width, int32_t height) = 0;
    virtual void delete_buffers() = 0;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual uint32_t get_texture() = 0;

protected:
    uint32_t mFBO = 0;
    uint32_t mTexId = 0;
    uint32_t mDepthId = 0;
    int32_t mWidth = 0;
    int32_t mHeight = 0;
};

class OpenGL_FrameBuffer : public FrameBuffer {
public:
    void create_buffers(int32_t width, int32_t height) override;
    void delete_buffers() override;

    void bind() override;
    void unbind() override;

    uint32_t get_texture() override;
};

};  // namespace meov::core
