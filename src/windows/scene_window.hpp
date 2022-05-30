#pragma once

#include "windows/base_window.hpp"
#include "event_manager.hpp"

namespace meov::core {
class FrameBuffer;
}  // namespace meov::core


namespace meov::Window {

class Scene final
    : public Base,
      public core::managers::MouseManager::Listener {
    using button = core::managers::MouseManager::Button;

public:
    Scene();
    Scene(int32_t width, int32_t height);
    ~Scene();

    void Select(std::shared_ptr<core::FrameBuffer> framebuffer);

protected:
    std::shared_ptr<core::FrameBuffer> mFrameBuffer{ nullptr };
    button mListenButton{ button::Middle };

    void DrawImpl() override;

    void OnMousePressed(button button, const glm::vec2 &position) override;
    void OnMouseReleased(button button, const glm::vec2 &position) override;

    bool HasIntersection(const glm::vec2 &pos) const;
};

}  // namespace meov::Window
