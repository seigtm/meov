#include "move_component.hpp"

#include "common.hpp"

#include "holder.hpp"
#include "transform_component.hpp"

#include "event_manager.hpp"

namespace meov::core::components {

MoveComponent::MoveComponent()
    : Component{ "Move component" } {
}

void MoveComponent::Draw(Graphics &g) {
}

void MoveComponent::Update(double delta) {
    if(!Valid())
        return;

    if(!managers::KeyboardManager::IsKeyPressed(SDLK_w) && !managers::KeyboardManager::IsKeyPressed(SDLK_s) && !managers::KeyboardManager::IsKeyPressed(SDLK_a) && !managers::KeyboardManager::IsKeyPressed(SDLK_d)) {
        return;
    }

    auto transform{ mHolder.lock()->GetComponent<TransformComponent>() };

    const auto forward{ glm::normalize(transform->GetForwardDirection()) };
    const auto right{ glm::normalize(transform->GetRightDirection()) };

    glm::vec3 force;
    if(managers::KeyboardManager::IsKeyPressed(SDLK_w)) {
        force = forward * mSpeed;
    } else if(managers::KeyboardManager::IsKeyPressed(SDLK_s)) {
        force = -forward * mSpeed;
    }

    if(managers::KeyboardManager::IsKeyPressed(SDLK_a)) {
        force = right * mSpeed;
    } else if(managers::KeyboardManager::IsKeyPressed(SDLK_d)) {
        force = -right * mSpeed;
    }

    transform->Move(force * static_cast<float>(delta));
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

    ImGui::InputFloat3("Velocity", glm::value_ptr(mVelocity));
    ImGui::InputFloat("Speed", &mSpeed);

    ImGui::Unindent();
}

bool MoveComponent::Valid() const {
    if(auto holder{ mHolder.lock() }; holder)
        return holder->GetComponent<TransformComponent>() != nullptr;
    return false;
}

}  // namespace meov::core::components
