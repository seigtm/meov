#include "windows/Log.hpp"

namespace MEOV::Window {

Log::Log()
    : Base{ "Log" } {}

void Log::Update(std::vector<plog::util::nstring>* messages) {
    _messages = messages;
}

void Log::DrawImpl() {
    if(!_messages)
        return;

    if(ImGui::Button("Clear"))
        _messages->clear();

    // Create scroll area with border and enable horizontal scrollbar.
    if(ImGui::BeginChild("Scrolling", {}, true, ImGuiWindowFlags_HorizontalScrollbar)) {
        // Clipper helps us to render only visible log messages.
        ImGuiListClipper clipper;
        clipper.Begin(_messages->size());
        while(clipper.Step())
            for(int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
                ImGui::TextUnformatted(plog::util::toNarrow(_messages->at(i), plog::codePage::kActive).c_str());
        clipper.End();
    }
    ImGui::EndChild();
}

}  // namespace MEOV::Window
