#pragma once

#include <glm/glm.hpp>

#include "core/object/components/component.hpp"
#include "core/event_manager/event_manager.hpp"

namespace meov::core {
class Graphics;
}  // namespace meov::core


namespace meov::core::components {

class TransformComponent;

namespace camera::defaults {

constexpr float Yaw{ 270.0f };
constexpr float Pitch{};
constexpr float Sensitivity{ 0.1f };
constexpr float Zoom{ 35.0f };
constexpr float Near{ .001f };
constexpr float Far{ 1000.f };

}  // namespace camera::defaults


class CameraComponent final
    : public Component,
      public managers::MouseManager::Listener {
    using button = core::managers::MouseManager::Button;

public:
    explicit CameraComponent(std::weak_ptr<Graphics> &&graphics,
                             float yaw = camera::defaults::Yaw,
                             float pitch = camera::defaults::Pitch);
    ~CameraComponent() override;

    void Draw(Graphics &) override;
    void Update(double delta) override;
    void Serialize() override;

    bool Valid() const;

private:
    std::weak_ptr<Graphics> mWeakGraphics;
    glm::mat4 mViewMatrix{ 1 };
    glm::mat4 mProjection{ 1 };

    button mListenButton{ button::Middle };
    glm::vec2 mLastMouseCoords{};
    bool mIsMouseGrabbed{ false };

    float mYaw;
    float mPitch;
    float mSensitivity{ camera::defaults::Sensitivity };
    float mZoom{ camera::defaults::Zoom };
    float mNear{ camera::defaults::Near };
    float mFar{ camera::defaults::Far };

    bool mConstrainPitch{ true };

    void UpdateDirections(TransformComponent &transform);
    void UpdateView(TransformComponent &transform);
    void UpdateProjection(const glm::vec2 screenSize);

    void OnMousePressed(managers::MouseManager::Button button, const glm::vec2 &position) override;
    void OnMouseReleased(managers::MouseManager::Button button, const glm::vec2 &position) override;
    void OnMouseMove(const glm::vec2 &position) override;
    // void OnMouseScroll(const glm::vec2 &direction) override;
};

}  // namespace meov::core::components
