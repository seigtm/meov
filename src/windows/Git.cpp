#include "windows/Git.hpp"
#include "AppInfo.hpp"
#include "Common.hpp"

namespace MEOV::Window {

Git::Git()
    : Base{ "Git information", ImVec2{ 400, 800 }, true, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize } {}

Git::~Git() {}

void Git::DrawImpl() {
    ImGui::Text("Git hash:    %s", MEOV::AppInfo::GitCommitHash().c_str());
    ImGui::Text("Git message: %s", MEOV::AppInfo::GitCommitMessage().c_str());
    ImGui::Text("Git date:    %s", MEOV::AppInfo::GitCommitDate().c_str());
}

}  // namespace MEOV::Window
