#include "common.hpp"
#include "holder.hpp"
#include "transform_component.hpp"
#include "model_component.hpp"
#include "ImGuiFileDialog.h"
#include "resource_manager.hpp"

namespace meov::core::components {

ModelComponent::ModelComponent(const fs::path &model)
    : Component{ "Model component" }
    , mPath{ model }
    , mModel{ RESOURCES->LoadModel(model) } {}

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

    ImGui::Text("Path: %s", mPath.string().c_str());
    ImGui::SameLine();
    if(ImGui::Button("Change")) {
        dialog->OpenModal(DialogName.data(), "Choose model", Extensions.data(), ".");
    }
    if(dialog->Display(DialogName.data())) {
        if(dialog->IsOk()) {
            mPath = dialog->GetFilePathName().erase(0, fs::current_path().string().size() + 1);
            mModel = RESOURCES->LoadModel(mPath);
        }
        dialog->Close();
    }
}

bool ModelComponent::Valid() const {
    const auto holder{ mHolder.lock() };
    return holder && mModel;
}

}  // namespace meov::core::components
