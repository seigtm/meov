#include "common.hpp"

#include "graphics.hpp"
#include "impl_factory.hpp"

#include "resource_manager.hpp"

namespace meov::core {


Graphics::Graphics()
    : mImpl{ factories::ImplFactory::Instance()->MakeGraphicsImpl() } {
    PushProgram(*RESOURCES->LoadProgram("shaders/default"));
}

void Graphics::SetViewMatrix(const glm::mat4 &view) {
    if(mImpl) mImpl->SetViewMatrix(view);
}
void Graphics::SetProjection(const glm::mat4 &projection) {
    if(mImpl) mImpl->SetProjection(projection);
}

const glm::mat4 &Graphics::GetViewMatrix() const {
    if(mImpl) return mImpl->GetViewMatrix();
    return {};
}
const glm::mat4 &Graphics::GetProjection() const {
    if(mImpl) return mImpl->GetProjection();
    return {};
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
void Graphics::DrawModel(const Model &model) {
    if(mImpl) mImpl->DrawModel(model);
}

Graphics::Impl::Impl() {
    PushColor(DefaultColor);
    PushTransform(DefaultTransform);
}

void Graphics::Impl::SetViewMatrix(const glm::mat4 &view) {
    mView = view;
}
void Graphics::Impl::SetProjection(const glm::mat4 &projection) {
    mProjection = projection;
}

const glm::mat4 &Graphics::Impl::GetViewMatrix() const {
    return mView;
}
const glm::mat4 &Graphics::Impl::GetProjection() const {
    return mProjection;
}


void Graphics::Impl::PushColor(const glm::u8vec4 &color) {
    mColorQueue.push_back(color);
}
void Graphics::Impl::PopColor() {
    if(mColorQueue.size() != 1) mColorQueue.pop_back();
}
glm::u8vec4 Graphics::Impl::CurrentColor() const {
    if(mColorQueue.empty())
        return {};
    return mColorQueue.back();
}

void Graphics::Impl::PushTransform(const glm::mat4 &transform) {
    mTransformQueue.push_back(transform);
}
void Graphics::Impl::PopTransform() {
    if(mTransformQueue.size() == 1)
        return;
    mTransformQueue.pop_back();
}
glm::mat4 Graphics::Impl::CurrentTransform() const {
    if(mTransformQueue.empty())
        return glm::mat4{ 1 };
    return mTransformQueue.back();
}
glm::mat4 Graphics::Impl::ResultingTransform() const {
    return std::reduce(
        mTransformQueue.begin(),
        mTransformQueue.end(),
        glm::mat4{ 1 },
        std::multiplies<glm::mat4>());
}

void Graphics::Impl::PushProgram(const shaders::Program &program) {
    if(program.IsValid()) mProgramQueue.push_back(program);
}
void Graphics::Impl::PopProgram() {
    if(!mProgramQueue.empty()) mProgramQueue.pop_back();
}
shaders::Program Graphics::Impl::CurrentProgram() const {
    if(mProgramQueue.empty())
        return {};
    return mProgramQueue.back();
}

}  // namespace meov::core
