#include "windows/Log.hpp"

namespace meov::Window {

Log::Log(std::string_view const title)
    : Base{ title } {}

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
        clipper.Begin(storage->size());
        while(clipper.Step())
            for(int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
                ImGui::TextUnformatted(plog::util::toNarrow(storage->at(i), plog::codePage::kActive).c_str());
        clipper.End();
    }
    ImGui::EndChild();
}

}  // namespace meov::Window
