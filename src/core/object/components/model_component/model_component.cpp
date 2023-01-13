#include <common>
#include <utils/scope_wrapper/scope_wrapper.hpp>

#include "ImGuiFileDialog.h"

#include "core/object/components/model_component/model_component.hpp"
#include "core/object/components/holder.hpp"
#include "core/object/components/transform_component/transform_component.hpp"
#include "core/resources/manager/resource_manager.hpp"
#include "core/model/model.hpp"

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
    auto transform{ GetHolder().lock()->GetComponent<TransformComponent>() };
    if(transform) transform->PushTransform(g);
    mModel->Draw(g);
    if(transform) transform->PopTransform(g);
}

void ModelComponent::Update(const f64 delta) { }

void ModelComponent::Serialize() {
    const auto valid{ Valid() };
    if(!valid) ImGui::PushStyleColor(ImGuiCol_Header, { 0.6f, 0.1f, 0.3f, 1.0f });
    if(!ImGui::CollapsingHeader(Name().c_str())) {
        if(!valid) ImGui::PopStyleColor();
        return;
    }

    utils::ScopeWrapper wrapper{ [] { ImGui::Indent(); }, [] { ImGui::Unindent(); } };

    if(!valid) {
        ImGui::PopStyleColor();
        ImGui::Text("Error: %s", mModel == nullptr ? "Invalid model!" : "Invalid holder!");
        ShowChangeModelDialog();
        return;
    }

    ShowChangeModelDialog();

    if(ImGui::TreeNode("Meshes")) {
        for(const auto &mesh : mModel->GetMeshes()) {
            Serialize(mesh);
        }
        ImGui::TreePop();
    }
}

bool ModelComponent::Reset(const std::shared_ptr<core::Model> &model) {
    if(model == nullptr)
        return false;
    mModel = model;
    return true;
}

bool ModelComponent::Valid() const {
    return !GetHolder().expired() && mModel;
}

void ModelComponent::Serialize(const std::shared_ptr<Mesh> &mesh) {
    if(mesh == nullptr)
        return;


    const std::string name{ mesh->Name() + " #" + std::to_string(mesh->GetID()) };
    if(!ImGui::TreeNode(name.c_str()))
        return;

    static constexpr std::array types{
        resources::Texture::Type::Diffuse,
        resources::Texture::Type::Specular,
        resources::Texture::Type::Height,
        resources::Texture::Type::Normal,
        resources::Texture::Type::Ambient,
        resources::Texture::Type::Cubemap,
    };

    const auto &material{ mesh->Material() };
    for(const auto &type : types) {
        const auto texture{ material[type] };
        if(texture == nullptr) continue;
        if(ImGui::TreeNode(resources::Texture::Type2String(type).data())) {
            if(texture->Valid()) {
                constexpr f32 size{ 256.f };
                const auto id{ texture->GetID() };
                ImGui::Image(reinterpret_cast<void *>(id), ImVec2{ size, size });
            }
            ImGui::Text("Name: %s", texture->Name().c_str());
            ImGui::Text("Path: %s", texture->GetPath().string().c_str());
            ImGui::TreePop();
        }
    }

    ImGui::TreePop();
}

void ModelComponent::ShowChangeModelDialog() {
    auto *dialog{ ImGuiFileDialog::Instance() };
    constexpr std::string_view DialogName{ "ChooseFileDlgKey" };
    constexpr std::string_view Extensions{ ".obj,.gltf,.fbx,.stl" };

    if (mModel) {
        ImGui::Text("Name: %s", mModel->Name().c_str());
        ImGui::Text("Path: %s", mModel->GetPath().string().c_str());
    }
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

}

}  // namespace meov::core::components
