#pragma once

#include "Common.hpp"
#include "Utilites.hpp"
#include "LogUtils.hpp"
#include "windows/Base.hpp"

namespace MEOV::Window {

class Log final : public Base, public MEOV::Utils::Singleton<Log> {
public:
    Log()
        : Base{ "Log" } {}

    void Update(std::vector<plog::util::nstring>* messages) {
        _messages = messages;
    }

protected:
    void DrawImpl() override final {
        if(!_messages)
            return;

        if(ImGui::Button("Clear log buffer"))
            _messages->clear();

        // Clipper helps us to render only visible log messages.
        ImGuiListClipper clipper;
        clipper.Begin(_messages->size());
        while(clipper.Step())
            for(int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
                ImGui::TextUnformatted(plog::util::toNarrow(_messages->at(i), plog::codePage::kActive).c_str());
        clipper.End();
    }

private:
    std::vector<plog::util::nstring>* _messages;
};

}  // namespace MEOV::Window
