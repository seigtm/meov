#include "Common.hpp"

#include "OGLFrameBuffer.hpp"

namespace meov::core::gl {

FrameBufferImplementation::FrameBufferImplementation(int32_t width, int32_t height)
    : mWidth{ width >= 0 ? width : 1280 }
    , mHeight{ height >= 0 ? height : 760 }
{
    // Creating framebuffer object
    glGenFramebuffers(1, &mFBO);

    // Creating a color attachment texture
    glGenTextures(1, &mTexId);
    glBindTexture(GL_TEXTURE_2D, mTexId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // create a renderbuffer object for depth and stencil attachment
    glGenRenderbuffers(1, &mRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);

    // attach the texture and the renderbuffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mRBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexId, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

    if (GLenum status{ glCheckFramebufferStatus(GL_FRAMEBUFFER) };
        status != GL_FRAMEBUFFER_COMPLETE) {
        LOGE << "Cannot initialize framebuffer (#" << static_cast<int>(status) << ")";
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

FrameBufferImplementation::~FrameBufferImplementation() {
    if (mFBO == 0) return;

    glDeleteTextures(1, &mTexId);
    glDeleteRenderbuffers(1, &mRBO);
    glDeleteFramebuffers(1, &mFBO);
    mTexId = mRBO = mFBO = 0;
}

void FrameBufferImplementation::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, mWidth, mHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBufferImplementation::UnBind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
}

uint32_t FrameBufferImplementation::GetFrameTexture() {
    return mTexId;
}

};  // namespace meov::core::gl
