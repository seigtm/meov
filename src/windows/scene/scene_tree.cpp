#include "common.hpp"

#include "scene_tree.hpp"
#include "object.hpp"
#include "scene.hpp"

namespace {

void drawObjects(const std::vector<std::shared_ptr<meov::core::Object>> &objects);

} // anonymous namespace

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
    if (!ImGui::CollapsingHeader("root"))
        return;

    const ImVec4 selectColor{ 234 / 255.f, 179 / 255.f, 123 / 255.f, 255.f };

    drawObjects(scene->GetObjects());
}

}  // namespace meov::Window

namespace {

void drawObjects(const std::vector<std::shared_ptr<meov::core::Object>> &objects) {
    if (objects.empty())
        return;

    hierarchy
    for (auto &&object : objects) {
        bool selected{ object->IsSelected() };
        const auto name{ object->Name() };
        ImGui::Checkbox(("##" + name).c_str(), &selected);
        object->SetSelect(selected);
        ImGui::SameLine();
        if (ImGui::TreeNode(name.c_str())) {
            drawObjects(object->children());
            ImGui::TreePop();
        }
    }
}

} // anonymous namespace

