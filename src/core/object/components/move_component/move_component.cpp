#include "move_component.hpp"

#include "common.hpp"

#include "holder.hpp"
#include "transform_component.hpp"

namespace meov::core::components {

MoveComponent::MoveComponent()
    : Component{ "Move component" } {
}

void MoveComponent::Draw(Graphics &g) {
}

void MoveComponent::Update(double delta) {
}

void MoveComponent::Serialize() {
    if(!ImGui::CollapsingHeader(Name().c_str())) return;
    ImGui::Text("Position:");
}

}  // namespace meov::core::components
