#pragma once

#include <glm/glm.hpp>

#include "component.hpp"

namespace meov::core {
class Graphics;
}  // namespace meov::core


namespace meov::core::components {

class TransformComponent;

namespace camera::defaults {

constexpr float Yaw{ -90.0f };
constexpr float Pitch{};
constexpr float Sensitivity{ 0.1f };
constexpr float Zoom{ 35.0f };
constexpr float Near{ .001f };
constexpr float Far{ 1000.f };

}  // namespace camera::defaults


class CameraComponent final : public Component {
public:
    explicit CameraComponent(std::weak_ptr<Graphics> &&graphics,
                             float yaw = camera::defaults::Yaw,
                             float pitch = camera::defaults::Pitch);
    ~CameraComponent() override = default;

    void Draw(Graphics &) override;
    void Update(double delta) override;
    void Serialize() override;

    bool Valid() const;

private:
    std::weak_ptr<Graphics> mWeakGraphics;
    glm::mat4 mViewMatrix{ 1 };
    glm::mat4 mProjection{ 1 };

    float mYaw;
    float mPitch;
    float mSensitivity{ camera::defaults::Sensitivity };
    float mZoom{ camera::defaults::Zoom };
    float mNear{ camera::defaults::Near };
    float mFar{ camera::defaults::Far };

    void UpdateDirections(TransformComponent &transform);
    void UpdateView(TransformComponent &transform);
    void UpdateProjection(const glm::vec2 screenSize);
};

}  // namespace meov::core::components
