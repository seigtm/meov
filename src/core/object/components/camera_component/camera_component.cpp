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
    if(!Valid())
        return;
    auto holder{ mHolder.lock() };
    auto graphics{ mWeakGraphics.lock() };
    if(graphics == nullptr)
        return;
    auto transform{ holder->GetComponent<TransformComponent>() };

    UpdateDirections(*transform);
    UpdateView(*transform);

    auto program{ graphics->CurrentProgram() };
    program.Use();
    program.Get("projection")->Set(mProjection);
    program.Get("view")->Set(mViewMatrix);
    program.UnUse();
}

void CameraComponent::Serialize() {
    const bool valid{ Valid() };
    if(!valid) ImGui::PushStyleColor(ImGuiCol_Header, { 0.6f, 0.1f, 0.3f, 1.0f });
    if(!ImGui::CollapsingHeader(Name().c_str())) {
        if(!valid) ImGui::PopStyleColor();
        return;
    }
    ImGui::Indent();
    if(!valid) {
        ImGui::PopStyleColor();
        auto holder{ mHolder.lock() };
        if(holder == nullptr)
            return;
        ImGui::Text("Would you like to add TransformComponent?");
        if(ImGui::Button("Add transform component")) {
            holder->AddComponent<TransformComponent>();
        }
        return;
    }

    ImGui::Text("Yaw | Pitch: [%.2f | %.2f]", mYaw, mPitch);
    ImGui::InputFloat("Sensitivity", &mSensitivity);
    ImGui::InputFloat("Zoom", &mZoom);
    ImGui::Spacing();
    ImGui::Text("View matrix:");
    ImGui::InputFloat4("| 0", glm::value_ptr(mViewMatrix[0]));
    ImGui::InputFloat4("| 1", glm::value_ptr(mViewMatrix[1]));
    ImGui::InputFloat4("| 2", glm::value_ptr(mViewMatrix[2]));
    ImGui::InputFloat4("| 3", glm::value_ptr(mViewMatrix[3]));
    ImGui::Spacing();
    ImGui::Text("Projection matrix:");
    ImGui::InputFloat4("| 0", glm::value_ptr(mProjection[0]));
    ImGui::InputFloat4("| 1", glm::value_ptr(mProjection[1]));
    ImGui::InputFloat4("| 2", glm::value_ptr(mProjection[2]));
    ImGui::InputFloat4("| 3", glm::value_ptr(mProjection[3]));
    ImGui::Unindent();
}

bool CameraComponent::Valid() const {
    auto holder{ mHolder.lock() };
    return !mWeakGraphics.expired() && holder && holder->GetComponent<TransformComponent>();
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
    const glm::vec3 position{ transform.GetPosition() };
    mViewMatrix = glm::lookAt(
        position,
        position + transform.GetForwardDirection(),
        transform.GetUpDirection());
}

}  // namespace meov::core::components
