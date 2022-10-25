#include "frame_buffer.hpp"

#include "impl_factory.hpp"

namespace meov::core {

FrameBuffer::FrameBuffer(int32_t width, int32_t height)
    : mImpl{ factories::ImplFactory::Instance()->MakeFrameBufferImpl(width, height) } {
}

void FrameBuffer::Bind() {
    if(mImpl) mImpl->Bind();
}
void FrameBuffer::UnBind() {
    if(mImpl) mImpl->UnBind();
}

uint32_t FrameBuffer::GetFrameTexture() const {
    if(mImpl) return mImpl->GetFrameTexture();
    return 0;
};

int32_t FrameBuffer::Width() const {
    if(mImpl) return mImpl->Width();
    return 0;
}
int32_t FrameBuffer::Height() const {
    if(mImpl) return mImpl->Height();
    return 0;
}

FrameBuffer::Impl::Impl(int32_t width, int32_t height)
    : mWidth{ width }, mHeight{ height } {}

int32_t FrameBuffer::Impl::Width() const {
    return mWidth;
}
int32_t FrameBuffer::Impl::Height() const {
    return mHeight;
}

}  // namespace meov::core
