#include "common.hpp"

#include "object.hpp"

namespace meov::core {

Object::Object(std::string &&name)
    : mixin::Named{ std::move(name) } {
}

void Object::PreDraw(Graphics &g) {
    ForEachComponent([&g](components::Component::Shared &comp) { comp->PreDraw(g); });
}

void Object::Draw(Graphics &g) {
    ForEachComponent([&g](components::Component::Shared &comp) { comp->Draw(g); });
}

void Object::PostDraw(Graphics &g) {
    ForEachComponent([&g](components::Component::Shared &comp) { comp->PostDraw(g); });
}

void Object::PreUpdate(double delta) {
    ForEachComponent([&delta](components::Component::Shared &comp) { comp->PreUpdate(delta); });
}

void Object::Update(double delta) {
    ForEachComponent([&delta](components::Component::Shared &comp) { comp->Update(delta); });
}

void Object::PostUpdate(double delta) {
    ForEachComponent([&delta](components::Component::Shared &comp) { comp->PostUpdate(delta); });
}

void Object::Serialize() {
    if(!ImGui::CollapsingHeader(Name().c_str()))
        return;

    ImGui::PushID(Name().c_str());
    ImGui::Indent();
    ForEachComponent([](components::Component::Shared &comp) {
        comp->Serialize();
        ImGui::Separator();
    });
    ImGui::Unindent();
    ImGui::PopID();
    ImGui::Spacing();
}

bool Object::Enabled() const {
    return mEnabled;
}
void Object::Enable() {
    mEnabled = true;
}
void Object::Disable() {
    mEnabled = false;
}


}  // namespace meov::core
