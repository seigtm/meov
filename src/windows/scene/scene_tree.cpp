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

    ImGui::InputText("##Object name", &mNewObjectName);
    ImGui::SameLine();
    if (ImGui::Button("Add new object")) {
        scene->AddObjectsUnderSelected(mNewObjectName);
        mNewObjectName.clear();
    }
    ImGui::Separator();

    if (!ImGui::CollapsingHeader("root"))
        return;

    const ImVec4 selectColor{ 234 / 255.f, 179 / 255.f, 123 / 255.f, 255.f };

    Draw(scene->GetObjects());
}

void SceneTree::Draw(const std::vector<std::shared_ptr<meov::core::Object>> &objects) {
    if (objects.empty())
        return;

    for (auto &&object : objects) {
        bool selected{ object->IsSelected() };
        const auto name{ object->Name() };
        ImGui::Checkbox(("##" + name).c_str(), &selected);
        object->SetSelect(selected);
        ImGuiTreeNodeFlags flags{ ImGuiTreeNodeFlags_OpenOnArrow };
        if (selected)
            flags |= ImGuiTreeNodeFlags_Selected;
        if (object->childrenCount() == 0)
            flags |= ImGuiTreeNodeFlags_Leaf;
        ImGui::SameLine();
        if (ImGui::TreeNodeEx(name.c_str(), flags)) {
            Draw(object->children());
            ImGui::TreePop();
        }
    }
}

}  // namespace meov::Window
