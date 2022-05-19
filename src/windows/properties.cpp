#include "windows/properties.hpp"

#include "model.hpp"
#include "common.hpp"

namespace meov::Window {

Properties::Properties(ImVec2 const &size, bool isClosable)
    : Base{ "Properties", size, isClosable } {}

void Properties::Select(std::weak_ptr<core::Model> &&model) {
    mModelTarget = std::move(model);
}

void Properties::Select(std::weak_ptr<core::Texture> &&texture) {
    mTextureTarget = std::move(texture);
}

void Properties::Reset() {
    mModelTarget.reset();
    mTextureTarget.reset();
}

void Properties::DrawImpl() {
    DrawInfo(mModelTarget.lock());
    DrawInfo(mTextureTarget.lock());
}

void Properties::DrawInfo(std::shared_ptr<core::Model> model) const {
    if(!model)
        return;

    if(!ImGui::CollapsingHeader("Model"))
        return;

    DrawInfo(model->GetTransform());
}  // namespace meov::Window

void Properties::DrawInfo(std::shared_ptr<core::Texture> texture) const {
    if(!texture)
        return;

    if(!ImGui::CollapsingHeader("Texture"))
        return;

    ImGui::Text("Texture name: %d", texture->Activate(0));
    ImGui::Text("Texture id: %d", texture->GetID());
    ImGui::Text("Valid: %s", texture->Valid() ? "yes" : "no");
    if(texture->Valid()) {
        auto id{ texture->GetID() };
        ImGui::Image(&id, ImVec2{});
    }
}

void Properties::DrawInfo(glm::mat4 &transform) const {
    if(!ImGui::CollapsingHeader("Transform"))
        return;
    glm::vec3 position{ transform[3][0], transform[3][1], transform[3][2] };
    if(ImGui::InputFloat3("Position", glm::value_ptr(position))) {
        transform[3][0] = position[0];
        transform[3][1] = position[1];
        transform[3][2] = position[2];
    }

    glm::vec3 scale{ transform[0][0], transform[1][1], transform[2][2] };
    if(ImGui::InputFloat3("Scale", glm::value_ptr(scale))) {
        transform[0][0] = scale[0];
        transform[1][1] = scale[1];
        transform[2][2] = scale[2];
    }
}

}  // namespace meov::Window