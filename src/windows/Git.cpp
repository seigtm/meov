#include "windows/Git.hpp"
#include "AppInfo.hpp"
#include "Common.hpp"

namespace meov::Window {

Git::Git()
    : Base{ "Git information" } {}

void Git::DrawImpl() {
    ImGui::Text("Git hash:    %s", meov::AppInfo::GitCommitHash().c_str());
    ImGui::Text("Git message: %s", meov::AppInfo::GitCommitMessage().c_str());
    ImGui::Text("Git date:    %s", meov::AppInfo::GitCommitDate().c_str());
}

}  // namespace meov::Window
