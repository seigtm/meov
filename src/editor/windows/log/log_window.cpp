#include "editor/windows/log/log_window.hpp"

namespace meov::Window {

Log::Log(std::string_view const title, ImVec2 const &size)
    : Base{ title, size } {}

void Log::DrawImpl() {
    auto storage{ mStorage.lock() };
    if(storage == nullptr)
        return;

    if(ImGui::Button("Clear"))
        storage->clear();

    // Create scroll area with border and enable horizontal scrollbar.
    if(ImGui::BeginChild("Scrolling", {}, true, ImGuiWindowFlags_HorizontalScrollbar)) {
        // Clipper helps us to render only visible log messages.
        ImGuiListClipper clipper;
        clipper.Begin(storage->size(), ImGui::GetTextLineHeight());
        while(clipper.Step()) {
            for(int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i) {
                const auto &line{ plog::util::toNarrow(storage->at(i), plog::codePage::kActive) };
                ImGui::TextColored(GetColorFor(line), line.c_str());
            }
        }
        clipper.End();
    }
    ImGui::EndChild();
}

ImVec4 Log::GetColorFor(const std::string_view &line) {
    if(line.find("INFO") != line.npos) return ImVec4{ 0.0f, 0.9f, 0.2f, 1.0f };
    if(line.find("DEBUG") != line.npos) return ImVec4{ 0.16, 0.7, 0.83, 1.0f };
    if(line.find("WARN") != line.npos) return ImVec4{ 0.92f, 0.72f, 0.5f, 1.0f };
    if(line.find("ERROR") != line.npos) return ImVec4{ 0.85f, 0.1f, 0.2f, 1.0f };
    if(line.find("FATAL") != line.npos) return ImVec4{ 1.f, 0.0f, 0.0f, 1.0f };
    return ImVec4{ 0.9f, 0.9f, 0.9f, 1.0f };
}

}  // namespace meov::Window
