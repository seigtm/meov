#include "camera_component.hpp"

#include "holder.hpp"
#include "graphics.hpp"
#include "shaders_program.hpp"
#include "transform_component.hpp"

namespace meov::core::components {

CameraComponent::CameraComponent(std::weak_ptr<Graphics> &&graphics, float yaw, float pitch)
    : Component{ "Camera component" }
    , mWeakGraphics{ std::move(graphics) }
    , mYaw{ yaw }
    , mPitch{ pitch } {}

void CameraComponent::Draw(Graphics &) {}

void CameraComponent::Update(double delta) {
    auto holder{ mHolder.lock() };
    if(holder == nullptr)
        return;
    auto graphics{ mWeakGraphics.lock() };
    auto transform{ holder->GetComponent<TransformComponent>() };
    if(graphics == nullptr || transform == nullptr)
        return;

    UpdateDirections(*transform);
    UpdateView(*transform);

    auto program{ graphics->CurrentProgram() };
    program.Use();
    program.Get("projection")->Set(mProjection);
    program.Get("view")->Set(mViewMatrix);
    program.UnUse();
}

void CameraComponent::Serialize() {
    if(!ImGui::CollapsingHeader(Name().c_str())) return;
}

void CameraComponent::UpdateDirections(TransformComponent &transform) {
    const float radPitch{ glm::radians(mPitch) };
    const float radYaw{ glm::radians(mYaw) };
    transform.SetForwardDirection(glm::normalize(glm::vec3{
        glm::cos(radYaw) * cos(radPitch),
        glm::sin(radPitch),
        glm::sin(radYaw) * glm::cos(radPitch) }));
}

void CameraComponent::UpdateView(TransformComponent &transform) {
}

}  // namespace meov::core::components
