#include "common.hpp"

#include "windows/properties/properties_window.hpp"

#include "object.hpp"
#include "component.hpp"

namespace meov::Window {

Properties::Properties(ImVec2 const &size, bool isClosable)
    : Base{ "Properties", size, isClosable } {}

void Properties::Select(std::vector<std::weak_ptr<core::Object>> &&object) {
    mObjects = std::move(object);
}

void Properties::Reset() {
    mObjects.clear();
}

void Properties::DrawImpl() {
    for(auto &&weakObj : mObjects) {
        if(auto &&obj{ weakObj.lock() }; obj) {
            const auto &name{ obj->Name() };
            if(!ImGui::CollapsingHeader(name.c_str()))
                continue;

            ImGui::PushID(name.c_str());
            ImGui::Indent();
            obj->ForEachComponent([](core::components::Component::Shared &comp) {
                comp->Serialize();
                ImGui::Separator();
            });

            if (ImGui::BeginCombo("Components", "transform")) {
                ImGui::EndCombo();
            }
            if (ImGui::Button("Add component")) {
                // core::components::Factory::Build(obj, "component");
            }
            ImGui::Unindent();
            ImGui::PopID();
            ImGui::Spacing();
        }
    }
}

}  // namespace meov::Window
