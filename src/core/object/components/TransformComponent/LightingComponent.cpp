#include "common.hpp"

#include "LightingComponent.hpp"
#include "holder.hpp"
#include "graphics.hpp"

#include "TransformComponent.hpp"
#include "ModelComponent.hpp"

namespace meov::core::components {

LightingComponent::LightingComponent()
    : Component{ "Lighting component" } {
}

void LightingComponent::Draw(Graphics &g) {
}

void LightingComponent::Update(double delta) {
}

void LightingComponent::Serialize() {
    struct ErrorWrapper {
        bool mValid{ false };
        explicit ErrorWrapper(bool valid)
            : mValid{ valid } {
            if(!mValid)
                ImGui::PushStyleColor(ImGuiCol_Header, { 0.6f, 0.1f, 0.3f, 1.0f });
        }
        ~ErrorWrapper() {
            if(!mValid)
                ImGui::PopStyleColor();
        }
    };

    const bool valid{ Valid() };
    {
        ErrorWrapper ew{ valid };
        if(!ImGui::CollapsingHeader(Name().c_str())) {
            return;
        }
    }

    if(!valid) {
        auto holder{ mHolder.lock() };
        if(holder == nullptr) {
            ImGui::Text("Error! Holder not found!");
            return;
        }
        ImGui::Text("Error! I cannot find the following components:");
        if(!HasTransformComponent()) ImGui::Text("   > Transform component");
        ImGui::Text("Would you like to create them?");
        if(ImGui::Button("Create transform component")) {
            holder->AddComponent<TransformComponent>();
        }
        return;
    }
    ImGui::Checkbox("Enabled", &mEnabled);
}

bool LightingComponent::Valid() const {
    return HasTransformComponent();
}

bool LightingComponent::HasTransformComponent() const {
    if(auto holder{ mHolder.lock() }; holder)
        return holder->GetComponent<TransformComponent>() != nullptr;
    return false;
}

}  // namespace meov::core::components
