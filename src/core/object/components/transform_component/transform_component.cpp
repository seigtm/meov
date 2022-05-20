#include "common.hpp"

#include "transform_component.hpp"

namespace meov::core::components {

TransformComponent::TransformComponent()
    : Component{ "Transform component" } {}


void TransformComponent::Draw(Graphics &) {
}

void TransformComponent::Update(double) {
}

void TransformComponent::Serialize() {
    if(!ImGui::CollapsingHeader(Name().c_str())) return;

    auto &trans{ GetTransform() };
    glm::vec4 position{ trans[3] };
    if(ImGui::InputFloat3("Position", glm::value_ptr(position))) {
        trans[3] = std::move(position);
    }

    glm::vec3 scale{ trans[0][0], trans[1][1], trans[2][2] };
    if(ImGui::InputFloat3("Scale", glm::value_ptr(scale))) {
        trans[0][0] = scale[0];
        trans[1][1] = scale[1];
        trans[2][2] = scale[2];
    }

    // glm::vec3 rotation{
    //     glm::degrees(atan2f(trans[1][2], trans[2][2])),
    //     glm::degrees(atan2f(-trans[0][2], sqrtf(trans[1][2] * trans[1][2] + trans[2][2] * trans[2][2]))),
    //     glm::degrees(atan2f(trans[0][1], trans[0][0]))
    // };
    // if(ImGui::InputFloat3("Rotation", glm::value_ptr(rotation))) {
    //     glm::mat4 rotated{ 1 };
    //     rotated = glm::rotate(rotated, rotation.x, { 1.f, 0.f, 0.f });
    //     rotated = glm::rotate(rotated, rotation.y, { 0.f, 1.f, 0.f });
    //     rotated = glm::rotate(rotated, rotation.z, { 0.f, 0.f, 1.f });
    //     trans *= rotated;
    // }
}


}  // namespace meov::core::components
