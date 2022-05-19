#include "common.hpp"

#include "object.hpp"

namespace meov::core {

Object::Object(std::string &&name)
    : mixin::Named{ std::move(name) } {
}

void Object::Draw(Graphics &g) {
    ForEachComponent([&g](components::Component::Shared &comp) { comp->Draw(g); });
}

void Object::Update(double delta) {
    ForEachComponent([&delta](components::Component::Shared &comp) { comp->Update(delta); });
}

void Object::Serialize() {
    if(!ImGui::CollapsingHeader(Name().c_str()))
        return;

    ForEachComponent([](components::Component::Shared &comp) { comp->Serialize(); });
    ImGui::Spacing();
}

}  // namespace meov::core
