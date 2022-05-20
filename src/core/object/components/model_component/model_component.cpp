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
    auto transform{ mHolder.lock()->GetComponent<TransformComponent>() };
    if(transform) transform->PushTransform(g);
    if(Valid())
        mModel->Draw(g);
    if(transform) transform->PopTransform(g);
}

void ModelComponent::Update(double) {
}

void ModelComponent::Serialize() {
    struct ErrorWrapper {
        bool mValid{ false };
        explicit ErrorWrapper(bool valid)
            : mValid{ valid } {
            if(!mValid)
                ImGui::PushStyleColor(ImGuiCol_Header, { 0.6f, 0.1f, 0.3f, 1.0f });
        }
        ~ErrorWrapper() {
            if(!mValid)
                ImGui::PopStyleColor();
        }
    };

    {
        ErrorWrapper ew{ Valid() };
        if(!ImGui::CollapsingHeader(Name().c_str())) {
            return;
        }
    }

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
    return mModel != nullptr;
}

}  // namespace meov::core::components
