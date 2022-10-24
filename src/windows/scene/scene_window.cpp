#include "common.hpp"
#include "scene_window.hpp"

#include "frame_buffer.hpp"

namespace meov::Window {

Scene::Scene()
    : Base{ "Scene" } {
    core::managers::MouseManager::AddListener(this);
}

Scene::Scene(int32_t width, int32_t height)
    : Base{ "Scene" }
    , mFrameBuffer(std::make_shared<core::FrameBuffer>(width, height)) {
    core::managers::MouseManager::AddListener(this);
}

Scene::~Scene() {
    core::managers::MouseManager::RemoveListener(this);
}

void Scene::Select(std::shared_ptr<core::FrameBuffer> framebuffer) {
    mFrameBuffer = std::move(framebuffer);
}

void Scene::DrawImpl() {
    if(mFrameBuffer == nullptr)
        return;
    uint32_t textureID = mFrameBuffer->GetFrameTexture();
    ImGui::Image(reinterpret_cast<void *>(textureID), mSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
}

void Scene::OnMousePressed(button button, const glm::vec2 &position) {
    if(button != mListenButton)
        return;
    SDL_SetRelativeMouseMode(HasIntersection(position) ? SDL_TRUE : SDL_FALSE);
}
void Scene::OnMouseReleased(button button, const glm::vec2 &position) {
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool Scene::HasIntersection(const glm::vec2 &pos) const {
    if(pos.x < mPos.x || pos.y < mPos.y) return false;
    if(pos.x > mPos.x + mSize.x || pos.y > mPos.x + mSize.x) return false;
    return true;
}

}  // namespace meov::Window