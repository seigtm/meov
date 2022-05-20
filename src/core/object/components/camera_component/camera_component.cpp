#include "camera_component.hpp"

#include "graphics.hpp"
#include "shaders_program.hpp"
#include "holder.hpp"
#include "transform_component.hpp"

namespace meov::core::components {

CameraComponent::CameraComponent(
    std::weak_ptr<Graphics> &&graphics, const glm::vec3 &up, float yaw, float pitch)
    : Component{ "Camera component" }
    , mWorldUp{ up }
    , mWeakGraphics{ std::move(graphics) }
    , mYaw{ yaw }
    , mPitch{ pitch } {}

void CameraComponent::Draw([[maybe_unused]] Graphics &) {}

void CameraComponent::Update(double delta) {
    auto holder{ mHolder.lock() };
    if(holder == nullptr)
        return;
    auto graphics{ mWeakGraphics.lock() };
    auto transform{ holder->GetComponent<TransformComponent>() };
    if(graphics == nullptr || transform == nullptr)
        return;

    UpdateDirection(transform);

    auto program{ graphics->CurrentProgram() };
    program.Use();
    program.Get("projection")->Set(mProjection);
    program.Get("view")->Set(mViewMatrix);
    program.UnUse();
}

void CameraComponent::Serialize() {
    if(!ImGui::CollapsingHeader(Name().c_str())) return;
}

void CameraComponent::UpdateDirections(std::shared_ptr<TransformComponent> transform) {
    const float radPitch{ glm::radians(mPitch) };
    const float radYaw{ glm::radians(mYaw) };
    const glm::vec3 front{
        glm::cos(radYaw) * cos(radPitch),
        glm::sin(radPitch),
        glm::sin(radYaw) * glm::cos(radPitch)
    };
    transform->SetForwardDirection(glm::normalize(front));
}

}  // namespace meov::core::components
