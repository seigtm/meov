#include "Common.hpp"

#include "Graphics.hpp"
#include "ImplFactory.hpp"

namespace meov::core {


Graphics::Graphics()
    : mImpl{ factories::ImplFactory::Instance()->MakeGraphicsImpl() }  //
{}

void Graphics::PushColor(const glm::u8vec4 &color) {
    if(mImpl) mImpl->PushColor(color);
}
void Graphics::PopColor() {
    if(mImpl) mImpl->PopColor();
}

void Graphics::PushTransform(const glm::mat4 &transform) {
    if(mImpl) mImpl->PushTransform(transform);
}
void Graphics::PopTransform() {
    if(mImpl) mImpl->PopTransform();
}

void Graphics::PushProgram(const shaders::Program &program) {
    if(mImpl) mImpl->PushProgram(program);
}
void Graphics::PopProgram() {
    if(mImpl) mImpl->PopProgram();
}

void Graphics::DrawDot(const glm::vec3 &position, const float radius) {
    if(mImpl) mImpl->DrawDot(position, radius);
}
void Graphics::DrawLine(std::initializer_list<glm::vec3> &&vertices) {
    if(mImpl) mImpl->DrawLine(std::move(vertices));
}

void Graphics::DrawTriangle(const std::array<glm::vec3, 3> &positions) {
    if(mImpl) mImpl->DrawTriangle(positions);
}

void Graphics::DrawRectangle(const std::array<glm::vec3, 4> &positions) {
    if(mImpl) mImpl->DrawRectangle(positions);
}
void Graphics::DrawRectangle(const glm::vec3 &position, const float width, const float height) {
    if(!mImpl) return;

    mImpl->DrawRectangle({
        position,                                                 //
        { position.x + width, position.y, position.z },           //
        { position.x + width, position.y + height, position.z },  //
        { position.x, position.y + height, position.z }           //
    });
}

void Graphics::DrawTexture(const std::array<glm::vec3, 4> &positions, const std::shared_ptr<Texture> &tex) {
    if(mImpl) mImpl->DrawTexture(positions, tex);
}
void Graphics::DrawTexture(const std::shared_ptr<Texture> &tex, const glm::vec3 position, const float width, const float height) {
    if(!mImpl) return;

    mImpl->DrawTexture(
        {
            position,                                                 //
            { position.x + width, position.y, position.z },           //
            { position.x + width, position.y + height, position.z },  //
            { position.x, position.y + height, position.z }           //
        },                                                            //
        tex                                                           //
    );
}

void Graphics::DrawMesh(const Mesh &mesh) {
    if(mImpl) mImpl->DrawMesh(mesh);
}

Graphics::Impl::Impl() {
    PushColor(DefaultColor);
    PushTransform(DefaultTransform);
}

void Graphics::Impl::PushColor(const glm::u8vec4 &color) {
    mColorQueue.push(color);
}
void Graphics::Impl::PopColor() {
    if(mColorQueue.size() != 1) mColorQueue.pop();
}

void Graphics::Impl::PushTransform(const glm::mat4 &transform) {
    mTransformQueue.push(transform);
}
void Graphics::Impl::PopTransform() {
    if(mTransformQueue.size() != 1) mTransformQueue.pop();
}

void Graphics::Impl::PushProgram(const shaders::Program &program) {
    mProgramQueue.push(program);
}
void Graphics::Impl::PopProgram() {
    if(!mProgramQueue.empty()) mProgramQueue.pop();
}


}  // namespace meov::core