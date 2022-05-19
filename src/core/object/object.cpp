#include "common.hpp"

#include "object.hpp"

namespace meov::core {

Object::Object(std::string &&name)
    : mixin::Named{ std::move(name) } {
}

void Object::Draw(Graphics &g) {
    for(auto &&component : mComponents)
        component->Draw(g);
}

void Object::Update(double delta) {
    for(auto &&component : mComponents)
        component->Update(delta);
}

void Object::Serialize() {
    if(!ImGui::CollapsingHeader(Name().c_str()))
        return;

    for(auto &&component : mComponents)
        component->Serialize();

    ImGui::Spacing();
}

}  // namespace meov::core
