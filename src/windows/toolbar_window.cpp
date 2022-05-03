#include "windows/toolbar_window.hpp"

#include "ImGuiFileDialog.h"

#include "common.hpp"
#include "resource_manager.hpp"

namespace meov::Window {

ToolBar::ToolBar(std::shared_ptr<meov::core::Model> &model,
                 bool &done,
                 bool &showLog,
                 bool &showGit,
                 bool &showCamera,
                 bool &showScene)
    : Base{ "ToolBar" }
    , mModelPointer{ &model }
    , mDone{ &done }
    , mShowLog{ &showLog }
    , mShowGit{ &showGit }
    , mShowCamera{ &showCamera }
    , mShowScene{ &showScene } {}

void ToolBar::DrawImpl() {
    // Open file with ImGuiFileDialog.
    if(ImGui::Button("Open File"))
        // Open modal.
        ImGuiFileDialog::Instance()->OpenModal("ChooseFileDlgKey", "Choose File", ".obj,.gltf,.fbx", ".");
    // Display modal (should be separated from the 'open' call).
    if(ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if(ImGuiFileDialog::Instance()->IsOk()) {
            auto modelPath = ImGuiFileDialog::Instance()->GetFilePathName();
            if(mModelPointer)
                mModelPointer->swap(meov::core::resources::Manager::Instance()->LoadModel(modelPath));
            else
                LOGE << "ToolBar has no pointer to the model Object in it.";
        }
        ImGuiFileDialog::Instance()->Close();
    }

    // Close program.
    if(ImGui::Button("Close")) {
        *mDone = true;
    }

    // Toggle visibility of windows.
    ImGui::Text("View");
    ImGui::Checkbox("Log", mShowLog);
    ImGui::Checkbox("Git info", mShowGit);
    ImGui::Checkbox("Camera", mShowCamera);
    ImGui::Checkbox("Scene", mShowScene);
}

}  // namespace meov::Window
