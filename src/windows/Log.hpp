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

        // Small optimization:
        // BeginChild() returns `false` if the window is collapsed.
        // We probably don't want to update it's GUI in this case.
        if(ImGui::BeginChild("Scrolling"))
            for(auto&& msg : *_messages)
                ImGui::Text("%s", plog::util::toNarrow(msg, plog::codePage::kActive).c_str());
        ImGui::EndChild();
    }

private:
    std::vector<plog::util::nstring>* _messages;
};

}  // namespace MEOV::Window
