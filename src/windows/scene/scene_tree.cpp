#include "common.hpp"

#include "scene_tree.hpp"
#include "object.hpp"
#include "scene.hpp"

namespace meov::Window {

SceneTree::SceneTree() noexcept
    : Base{ "Scene tree" } {
}

void SceneTree::Select(std::weak_ptr<core::Scene> &&scene) {
    mWrappedScene = std::move(scene);
}

void SceneTree::DrawImpl() {
    auto scene{ mWrappedScene.lock() };
    if(scene == nullptr)
        return;

    const ImVec4 selectColor{ 234 / 255.f, 179 / 255.f, 123 / 255.f, 255.f };

    auto &objects{ scene->GetObjects() };
    for(auto &&obj : objects) {
        bool selected{ obj->IsSelected() };
        if(selected) ImGui::PushStyleColor(ImGuiCol_Button, selectColor);
        if(ImGui::Button(obj->Name().c_str())) {
            if(selected)
                obj->Deselect();
            else
                obj->Select();
        }
        if(selected) ImGui::PopStyleColor();
    }
}

}  // namespace meov::Window
