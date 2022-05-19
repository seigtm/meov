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
                 bool &showScene,
                 bool &showLightning)
    : Base{ "ToolBar" }
    , mModelPointer{ &model }
    , mDone{ &done }
    , mShowLog{ &showLog }
    , mShowGit{ &showGit }
    , mShowCamera{ &showCamera }
    , mShowScene{ &showScene }
    , mShowLightning{ &showLightning } {}

void ToolBar::setExtensions(const std::string_view ext)
{
    if (ext.empty())
        return;
    mExtensions = std::string{ ext };
}

void ToolBar::DrawImpl() {
    // Open file with ImGuiFileDialog.
    auto *dialog{ ImGuiFileDialog::Instance() };
    constexpr std::string_view DialogName{ "ChooseFileDlgKey" };
    if(ImGui::Button("Open File")) {
        // Open modal.
        dialog->OpenModal(DialogName.data(), "Choose File", mExtensions.c_str(), ".");
    }
    // Display modal (should be separated from the 'open' call).
    if(dialog->Display(DialogName.data())) {
        if(dialog->IsOk()) {
            auto modelPath = dialog->GetFilePathName();
            if(mModelPointer)
                mModelPointer->swap(meov::core::resources::Manager::Instance()->LoadModel(modelPath));
            else
                LOGE << "ToolBar has no pointer to the model Object in it.";
        }
        dialog->Close();
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
    ImGui::Checkbox("Lightning", mShowLightning);
    ImGui::Checkbox("Scene", mShowScene);
}

}  // namespace meov::Window
