#pragma once

#include <glm/glm.hpp>

#include "component.hpp"

namespace meov::core {
class Graphics;
}  // namespace meov::core


namespace meov::core::components {

class TransformComponent;

namespace camera::defaults {

static constexpr float Yaw{ -90.0f };
static constexpr float Pitch{};
static constexpr float Speed{ 50.f };
static constexpr float Sensitivity{ 0.1f };
static constexpr float Zoom{ 35.0f };

}  // namespace camera::defaults


class CameraComponent final : public Component {
public:
    CameraComponent(std::weak_ptr<Graphics> &&graphics,
                    const glm::vec3 &up = glm::vec3{ 0, 1, 0 },
                    float yaw = camera::defaults::Yaw,
                    float pitch = camera::defaults::Pitch);
    ~CameraComponent() override = default;

    void Draw(Graphics &) override;
    void Update(double) override;
    void Serialize() override;

    bool Valid() const;

private:
    std::weak_ptr<Graphics> mWeakGraphics;
    const glm::vec3 mWorldUp;
    glm::mat4 mViewMatrix{ 1 };
    glm::mat4 mProjection{ 1 };

    float mYaw;
    float mPitch;
    float mSpeed{ camera::defaults::Speed };
    float mMouseSensitivity{ camera::defaults::Sensitivity };
    float mZoom{ camera::defaults::Zoom };

    void UpdateDirections(std::shared_ptr<TransformComponent> transform);
    void UpdateView(std::shared_ptr<TransformComponent> transform);
};

}  // namespace meov::core::components
