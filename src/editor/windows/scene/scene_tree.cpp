#include <common>

#include <editor/windows/scene/scene_tree.hpp>

#include <core/resources/manager/resource_manager.hpp>
#include <core/resources/texture/texture.hpp>

#include <core/object/object.hpp>
#include <core/scene/scene.hpp>

namespace meov::Window {

SceneTree::SceneTree() noexcept
    : Base{ "Scene tree", MinSize }
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

    for (auto &&object : objects) {
        if (DrawTreeNode(object)) {
            Draw(object->children());
            ImGui::TreePop();
        }
    }
}

bool SceneTree::DrawTreeNode(const std::shared_ptr<core::Object> &object) {
    constexpr ImGuiTreeNodeFlags flags{ ImGuiTreeNodeFlags_None
        | ImGuiTreeNodeFlags_OpenOnArrow
        | ImGuiTreeNodeFlags_DefaultOpen
        | ImGuiTreeNodeFlags_FramePadding
        | ImGuiTreeNodeFlags_SpanAvailWidth
        | ImGuiTreeNodeFlags_AllowItemOverlap
    };
    constexpr std::string_view PayloadType{ "Object" };
    const auto &name{ object->Name() };
    const bool selected{ object->IsSelected() };

    ImGui::PushID(name.c_str());

    const bool toggled{ ImGui::TreeNodeEx(name.c_str(),
        flags | (object->empty() ? ImGuiTreeNodeFlags_Leaf     : ImGuiTreeNodeFlags_None)
              | (selected        ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None)
    ) };
    bool node_clicked{ false };
    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
        node_clicked = true;

    ImGui::PopID();

    // Drag & drop behavior
    if (ImGui::BeginDragDropSource()) {
        ImGui::SetDragDropPayload(PayloadType.data(), &object, sizeof(object));
        ImGui::Text(name.c_str());
        ImGui::EndDragDropSource();
    }

    if (ImGui::BeginDragDropTarget()) {
        if (const auto payload{ ImGui::AcceptDragDropPayload(PayloadType.data()) }; payload != nullptr) {
            const auto *dragObjectPtr{ static_cast<const std::shared_ptr<core::Object> *>(payload->Data) };
            if (dragObjectPtr == nullptr) {
                LOGE << "Payload data is nullptr";
                ImGui::EndDragDropTarget();
                return toggled;
            }
            auto dragObject{ *dragObjectPtr };

            if (dragObject != object) {
                if (auto parent{ dragObject->parent() }; parent)
                    parent->removeChild(dragObject);
                object->addChild(std::move(dragObject));
            }
        }
        ImGui::EndDragDropTarget();
    }

    // Selectable behavior
    // ImGui::SameLine();
    if (const auto id{ "##" + name }; node_clicked)
        object->SetSelect(!selected);

    ImGui::SameLine();

    const auto xPosition{ ImGui::CalcItemWidth() - ImGui::GetFrameHeight() };
    ImGui::SetCursorPosX(xPosition);
    if (const bool enabled{ object->Enabled() }; ImageButton(enabled ? "visible" : "invisible")) {
        if (enabled)
            object->Disable();
        else
            object->Enable();
    }

    return toggled;
}

bool SceneTree::ImageButton(const std::string &icon, const ImColor &clr) const {
    const f32 size{ ImGui::GetFrameHeight() };

    return ImGui::ImageButton(
        reinterpret_cast<ImTextureID>(mIcons.at(icon)->GetID()),
        ImVec2{ size, size },
        ImVec2{ 0.f, 0.f }, // uv0
        ImVec2{ 1.f, 1.f }, // uv1
        0, // frame padding
        clr, // bg
        clr // tint color
    );
}

}  // namespace meov::Window
