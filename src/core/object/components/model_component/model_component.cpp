#include "common.hpp"
#include "holder.hpp"
#include "transform_component.hpp"
#include "model_component.hpp"
#include "ImGuiFileDialog.h"
#include "resource_manager.hpp"

namespace meov::core::components {

ModelComponent::ModelComponent(const fs::path &model)
    : Component{ "Model component" }
    , mModel{ RESOURCES->LoadModel(model) } {}

ModelComponent::ModelComponent(const std::shared_ptr<core::Model> &model)
    : Component{ "Model component" }
    , mModel{ model } {}

void ModelComponent::Draw(Graphics &g) {
    if(!Valid())
        return;
    auto transform{ mHolder.lock()->GetComponent<TransformComponent>() };
    if(transform) transform->PushTransform(g);
    mModel->Draw(g);
    if(transform) transform->PopTransform(g);
}

void ModelComponent::Update(double) {
}

void ModelComponent::Serialize() {
    if(!Valid()) ImGui::PushStyleColor(ImGuiCol_Header, { 0.6f, 0.1f, 0.3f, 1.0f });
    if(!ImGui::CollapsingHeader(Name().c_str())) {
        if(!Valid()) ImGui::PopStyleColor();
        return;
    }
    if(!Valid()) ImGui::PopStyleColor();

    auto *dialog{ ImGuiFileDialog::Instance() };
    constexpr std::string_view DialogName{ "ChooseFileDlgKey" };
    constexpr std::string_view Extensions{ ".obj,.gltf,.fbx,.stl" };
    ImGui::Indent();

    ImGui::Text("Name: %s", mModel->Name().c_str());
    ImGui::Text("Path: %s", mModel->GetPath().string().c_str());
    if(ImGui::Button("Change")) {
        dialog->OpenModal(DialogName.data(), "Choose model", Extensions.data(), ".");
    }
    if(dialog->Display(DialogName.data())) {
        if(dialog->IsOk()) {
            const auto path{ dialog->GetFilePathName().erase(0, fs::current_path().string().size() + 1) };
            mModel = RESOURCES->LoadModel(path);
        }
        dialog->Close();
    }

    if(ImGui::TreeNode("Meshes")) {
        for(const auto &mesh : mModel->GetMeshes()) {
            Serialize(mesh);
        }
        ImGui::TreePop();
    }

    ImGui::Unindent();
}

void ModelComponent::Serialize(const std::shared_ptr<Mesh> &mesh) {
    if(mesh == nullptr)
        return;


    const std::string name{ mesh->Name() + " #" + std::to_string(mesh->GetID()) };
    if(!ImGui::TreeNode(name.c_str()))
        return;

    static const std::array types{
        Texture::Type::Diffuse,
        Texture::Type::Specular,
        Texture::Type::Height,
        Texture::Type::Normal,
        Texture::Type::Ambient,
        Texture::Type::Cubemap,
    };

    const auto &material{ mesh->Material() };
    for(const auto &type : types) {
        const auto texture{ material[type] };
        if(texture == nullptr) continue;
        if(ImGui::TreeNode(Texture::Type2String(type).c_str())) {
            if(texture->Valid()) {
                constexpr float size{ 256.f };
                const auto id{ texture->GetID() };
                ImGui::Image(reinterpret_cast<ImTextureID>(id), ImVec2{ size, size });
            }
            ImGui::Text("Name: %s", texture->Name().c_str());
            ImGui::Text("Path: %s", texture->GetPath().string().c_str());
            ImGui::TreePop();
        }
    }

    ImGui::TreePop();
}

bool ModelComponent::Reset(const std::shared_ptr<core::Model> &model) {
    if(model == nullptr)
        return false;
    mModel = model;
    return true;
}

bool ModelComponent::Valid() const {
    const auto holder{ mHolder.lock() };
    return holder && mModel;
}

}  // namespace meov::core::components
