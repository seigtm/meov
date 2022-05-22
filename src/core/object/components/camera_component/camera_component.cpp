#include "camera_component.hpp"

#include "holder.hpp"
#include "graphics.hpp"
#include "shaders_program.hpp"
#include "transform_component.hpp"

namespace {

template<class T>
T RoundByRange(T value, const T Min, const T Max) {
    if(value < Min) return Min;
    if(value > Max) return Max;
    return value;
}

}  // namespace

namespace meov::core::components {

CameraComponent::CameraComponent(std::weak_ptr<Graphics> &&graphics, float yaw, float pitch)
    : Component{ "Camera component" }
    , mWeakGraphics{ std::move(graphics) }
    , mYaw{ yaw }
    , mPitch{ pitch } {
    managers::MouseManager::AddListener(this);
}

CameraComponent::~CameraComponent() {
    managers::MouseManager::RemoveListener(this);
}

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

    /// FIXME: Remove hardcoded shit
    ImGui::Begin("Scene");
    const auto [w, h]{ ImGui::GetWindowSize() };
    ImGui::End();
    UpdateProjection({ w, h });

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
        if(holder == nullptr) {
            ImGui::Unindent();
            return;
        }
        ImGui::Text("Would you like to add TransformComponent?");
        if(ImGui::Button("Add transform component")) {
            holder->AddComponent<TransformComponent>();
        }
        ImGui::Unindent();
        return;
    }

    ImGui::Text("Yaw: %.4f, Pitch: %.4f", mYaw, mPitch);
    ImGui::InputFloat("Sensitivity", &mSensitivity);
    ImGui::InputFloat("Zoom", &mZoom);
    ImGui::InputFloat("Near", &mNear);
    ImGui::InputFloat("Far", &mFar);
    ImGui::Checkbox("Constrain pitch", &mConstrainPitch);
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
    transform.SetForwardDirection(glm::vec3{
        glm::cos(radYaw) * cos(radPitch),
        glm::sin(radPitch),
        glm::sin(radYaw) * glm::cos(radPitch) });
}

void CameraComponent::UpdateView(TransformComponent &transform) {
    const glm::vec3 position{ transform.GetPosition() };
    mViewMatrix = glm::lookAt(
        position,
        position + transform.GetForwardDirection(),
        transform.GetUpDirection());
}

void CameraComponent::UpdateProjection(const glm::vec2 screen) {
    mProjection = glm::perspective(glm::radians(mZoom), screen.x / screen.y, mNear, mFar);
}

void CameraComponent::OnMousePressed(
    managers::MouseManager::Button button, const glm::vec2 &position) {
    if(button != managers::MouseManager::Button::Left)
        return;

    mLastMouseCoords = position;
    mIsMouseGrabbed = true;
}

void CameraComponent::OnMouseReleased(
    managers::MouseManager::Button button, const glm::vec2 &position) {
    if(button != managers::MouseManager::Button::Left)
        return;

    mIsMouseGrabbed = false;
}


void CameraComponent::OnMouseMove(const glm::vec2 &position) {
    if(!mIsMouseGrabbed)
        return;

    const glm::vec2 offset{
        position.x - mLastMouseCoords.x,
        mLastMouseCoords.y - position.y
    };
    mLastMouseCoords = position;

    mYaw += offset.x * mSensitivity;
    if(mYaw >= 360)
        mYaw = 0;
    else if(mYaw < 0)
        mYaw = 359 + mYaw;

    mPitch += offset.y * mSensitivity;
    if(mConstrainPitch) {
        constexpr float MaxPitch{ 89.0f };
        mPitch = RoundByRange(mPitch, -MaxPitch, MaxPitch);
    }
}

void CameraComponent::OnMouseScroll(const glm::vec2 &direction) {
    constexpr float MinZoom{ 0.0f };
    constexpr float MaxZoom{ 45.0f };
    mZoom = RoundByRange(mZoom - direction.y, MinZoom, MaxZoom);
}


}  // namespace meov::core::components
