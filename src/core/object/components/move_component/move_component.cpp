#include "core/object/components/move_component/move_component.hpp"

#include <common>

#include "core/object/components/holder.hpp"
#include "core/object/components/transform_component/transform_component.hpp"

#include "core/event_manager/event_manager.hpp"

namespace meov::core::components {

MoveComponent::MoveComponent()
    : Component{ "Move component" } {
}

void MoveComponent::Draw(Graphics &g) {
}

void MoveComponent::Update(double delta) {
    if(!Valid())
        return;

    auto transform{ mHolder.lock()->GetComponent<TransformComponent>() };
    mVelocity = GetDirection(*transform) * mSpeed * static_cast<float>(delta);
    transform->Move(mVelocity);
}

void MoveComponent::Serialize() {
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

    ImGui::DragFloat3("Velocity", glm::value_ptr(mVelocity));
    ImGui::InputFloat("Speed", &mSpeed);

    ImGui::Unindent();
}

bool MoveComponent::Valid() const {
    if(auto holder{ mHolder.lock() }; holder)
        return holder->GetComponent<TransformComponent>() != nullptr;
    return false;
}

glm::vec3 MoveComponent::GetDirection(TransformComponent &transform) const {
    using namespace managers;

    if(!KeyboardManager::IsAnyKeyPressed({ SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_q, SDLK_e })) {
        return {};
    }

    const auto forward{ transform.GetForwardDirection() };
    const auto right{ transform.GetRightDirection() };
    const auto up{ transform.GetUpDirection() };

    glm::vec3 direction{};
    if(KeyboardManager::IsKeyPressed(SDLK_a)) {
        direction += -right;
    }
    if(KeyboardManager::IsKeyPressed(SDLK_d)) {
        direction += right;
    }

    if(KeyboardManager::IsKeyPressed(SDLK_q)) {
        direction += up;
    }
    if(KeyboardManager::IsKeyPressed(SDLK_e)) {
        direction += -up;
    }

    if(KeyboardManager::IsKeyPressed(SDLK_w)) {
        direction += forward;
    }
    if(KeyboardManager::IsKeyPressed(SDLK_s)) {
        direction += -forward;
    }
    return direction;
}

}  // namespace meov::core::components
