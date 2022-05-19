#include "common.hpp"
#include "ModelComponent.hpp"
#include "ImGuiFileDialog.h"
#include "resource_manager.hpp"

namespace meov::core::components {

ModelComponent::ModelComponent(const fs::path &model)
    : Component{ "Model component" }
    , mPath{ model }
    , mModel{ RESOURCES->LoadModel(model) } {}

void ModelComponent::Draw(Graphics &g) {
    if(Valid())
        mModel->Draw(g);
}

void ModelComponent::Update(double) {
}

void ModelComponent::Serialize() {
    const ImVec4 red{ 0.9f, 0.1f, 0.3f, 1.0f };
    const ImVec4 white{ 0.9f, 0.9f, 0.9f, 1.0f };

    ImGui::PushStyleColor(ImGuiCol_Border, Valid() ? white : red);
    if(!ImGui::CollapsingHeader(Name().c_str())) {
        ImGui::PopStyleColor();
        return;
    }
    ImGui::PopStyleColor();

    auto *dialog{ ImGuiFileDialog::Instance() };
    constexpr std::string_view DialogName{ "ChooseFileDlgKey" };
    constexpr std::string_view Extensions{ ".obj,.gltf,.fbx,.stl" };

    ImGui::TextColored(Valid() ? white : red, "Path: %s", mPath.string().c_str());
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
    return mModel != nullptr;
}

}  // namespace meov::core::components
