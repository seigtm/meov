#include "common.hpp"

#include "graphics.hpp"
#include "impl_factory.hpp"

#include "resource_manager.hpp"

namespace meov::core {


Graphics::Graphics()
    : mImpl{ factories::ImplFactory::Instance()->MakeGraphicsImpl() } {
    PushProgram(*RESOURCES->LoadProgram("shaders/default"));
}

void Graphics::PushColor(const glm::u8vec4 &color) {
    if(mImpl) mImpl->PushColor(color);
}
void Graphics::PopColor() {
    if(mImpl) mImpl->PopColor();
}
glm::u8vec4 Graphics::CurrentColor() const {
    if(mImpl) return mImpl->CurrentColor();
    return {};
}

void Graphics::PushTransform(const glm::mat4 &transform) {
    if(mImpl) mImpl->PushTransform(transform);
}
void Graphics::PopTransform() {
    if(mImpl) mImpl->PopTransform();
}
glm::mat4 Graphics::CurrentTransform() const {
    if(mImpl) return mImpl->CurrentTransform();
    return {};
}

void Graphics::PushProgram(const shaders::Program &program) {
    if(mImpl) mImpl->PushProgram(program);
}
void Graphics::PopProgram() {
    if(mImpl) mImpl->PopProgram();
}
shaders::Program Graphics::CurrentProgram() const {
    if(mImpl) return mImpl->CurrentProgram();
    return {};
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
glm::u8vec4 Graphics::Impl::CurrentColor() const {
    if(mColorQueue.empty())
        return {};
    return mColorQueue.front();
}

void Graphics::Impl::PushTransform(const glm::mat4 &transform) {
    mTransformQueue.push(transform);
    mResultTransform *= transform;
}
void Graphics::Impl::PopTransform() {
    if(mTransformQueue.size() == 1)
        return;
    mResultTransform *= glm::inverse(mTransformQueue.front());
    mTransformQueue.pop();
}
glm::mat4 Graphics::Impl::CurrentTransform() const {
    if(mTransformQueue.empty())
        return glm::mat4{ 1 };
    return mTransformQueue.front();
}
glm::mat4 Graphics::Impl::ResultingTransform() const {
    return mResultTransform;
}

void Graphics::Impl::PushProgram(const shaders::Program &program) {
    mProgramQueue.push(program);
}
void Graphics::Impl::PopProgram() {
    if(!mProgramQueue.empty()) mProgramQueue.pop();
}
shaders::Program Graphics::Impl::CurrentProgram() const {
    if(mProgramQueue.empty())
        return {};
    return mProgramQueue.front();
}

}  // namespace meov::core
