#include "windows/base_window.hpp"

namespace meov::Window {

Base::Base(std::string_view const title, ImVec2 const& size, bool isClosable, ImGuiWindowFlags flags)
    : _title{ title }
    , _size{ size }
    , _isClosable{ isClosable }
    , _flags{ flags } {}

void Base::Draw() {
    ImGui::SetNextWindowSize(_size, ImGuiCond_Once);  // Resize will be called once per session.
    ImGui::Begin(_title.c_str(), &_isClosable, _flags);
    DrawImpl();
    ImGui::End();
}

void Base::ToggleNoTitleBar() {
    ToggleFlag(ImGuiWindowFlags_NoTitleBar);
}

void Base::ToggleNoScrollBar() {
    ToggleFlag(ImGuiWindowFlags_NoScrollbar);
}

void Base::ToggleAlwaysAutoResize() {
    ToggleFlag(ImGuiWindowFlags_AlwaysAutoResize);
}

void Base::ToggleNoMove() {
    ToggleFlag(ImGuiWindowFlags_NoMove);
}

void Base::ToggleNoResize() {
    ToggleFlag(ImGuiWindowFlags_NoResize);
}

void Base::ToggleFlag(ImGuiWindowFlags flag) {
    _flags ^= flag;
}

}  // namespace meov::Window
