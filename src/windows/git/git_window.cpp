#include "windows/git/git_window.hpp"
#include "app_info.hpp"
#include "common.hpp"

namespace meov::Window {

Git::Git()
    : Base{ "Git information" } {}

void Git::DrawImpl() {
    ImGui::Text("Git hash:    %s", meov::AppInfo::GitCommitHash().c_str());
    ImGui::Text("Git message: %s", meov::AppInfo::GitCommitMessage().c_str());
    ImGui::Text("Git date:    %s", meov::AppInfo::GitCommitDate().c_str());
}

}  // namespace meov::Window
