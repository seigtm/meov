#include "common.hpp"

#include "windows/properties/properties_window.hpp"

#include "object.hpp"
#include "component.hpp"
#include "factory.hpp"

namespace meov::Window {

Properties::Properties(ImVec2 const &size, bool isClosable)
    : Base{ "Properties", size, isClosable }
    , mComponents{ core::components::Factory::GetComponents() }
    , mSelectedComponent{ mComponents.begin() } {
}

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

            DrawComponentsDropBox();
            ImGui::SameLine();
            if (ImGui::Button("Add component")) {
                core::components::Factory::Build(obj, *mSelectedComponent);
            }
            ImGui::Unindent();
            ImGui::PopID();
            ImGui::Spacing();
        }
    }
}

void Properties::DrawComponentsDropBox() {
    if (!ImGui::BeginCombo("##Components", mSelectedComponent->c_str()))
        return;
    for (auto current{ mComponents.begin() }; current != mComponents.end(); ++current) {
        const bool isSelected{ mSelectedComponent == current };
        if (ImGui::Selectable(current->c_str(), isSelected))
            mSelectedComponent = current;

        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
        if (isSelected)
            ImGui::SetItemDefaultFocus();
    }

    ImGui::EndCombo();
}

}  // namespace meov::Window
