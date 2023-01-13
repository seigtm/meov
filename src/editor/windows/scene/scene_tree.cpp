#include <common>

#include <editor/windows/scene/scene_tree.hpp>

#include <core/resources/manager/resource_manager.hpp>
#include <core/resources/texture/texture.hpp>

#include <core/object/object.hpp>
#include <core/scene/scene.hpp>

namespace meov::Window {

SceneTree::SceneTree() noexcept
    : Base{ "Scene tree" }
    , mIcons{
        { "add", RESOURCES->LoadTexture("icons/plus_icon.png") },
        { "remove", RESOURCES->LoadTexture("icons/minus_icon.png") },
        { "visible", RESOURCES->LoadTexture("icons/eye.png") },
        { "invisible", RESOURCES->LoadTexture("icons/eye_hidden.png") },
    } {
}

void SceneTree::Select(std::weak_ptr<core::Scene> &&scene) {
    mWrappedScene = std::move(scene);
}

void SceneTree::DrawImpl() {
    auto scene{ mWrappedScene.lock() };
    if(scene == nullptr)
        return;

    if (ImageButton("add")) {
        scene->AddObjectsUnderSelected("Object");
    }
    ImGui::SameLine();
    if (ImageButton("remove")) {
        for (auto weakObject : scene->GetSelectedObjects()) {
            if (auto object{ weakObject.lock() }; object)
                object->IWannaDead();
        }
    }

    ImGui::Separator();

    Draw(scene->GetObjects());
}

void SceneTree::Draw(const std::vector<sptr<core::Object>> &objects) {
    if (objects.empty())
        return;

    auto drawLine = [&] (sptr<core::Object> object, const std::string &name) {
        ImGuiTreeNodeFlags flags{ ImGuiTreeNodeFlags_OpenOnArrow };
        bool selected{ object->IsSelected() };
        if (ImGui::Checkbox(("##" + name).c_str(), &selected))
            object->SetSelect(selected);
        if (selected)
            flags |= ImGuiTreeNodeFlags_Selected;
        if (object->childrenCount() == 0)
            flags |= ImGuiTreeNodeFlags_Leaf;
        ImGui::SameLine();
        const bool toggled{ ImGui::TreeNodeEx(name.c_str(), flags) };
        ImGui::SameLine();
        if (const bool enabled{ object->Enabled() }; ImageButton(enabled ? "visible" : "invisible")) {
            if (enabled)
                object->Disable();
            else
                object->Enable();
        }
        return toggled;
    };

    for (auto &&object : objects) {
        if (drawLine(object, object->Name())) {
            Draw(object->children());
            ImGui::TreePop();
        }
    }
}

bool SceneTree::ImageButton(const std::string &icon, const ImColor &clr) const {
    const f32 size{ ImGui::GetTextLineHeightWithSpacing() };
    const ImVec2 buttonSize{ size, size };
    const ImVec2 uv0{};
    const ImVec2 uv1{ 1, 1 };

    return ImGui::ImageButton(
        reinterpret_cast<ImTextureID>(mIcons.at(icon)->GetID()), buttonSize, uv0, uv1, 0, {}, clr);
}

}  // namespace meov::Window
