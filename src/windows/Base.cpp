#include "windows/Base.hpp"

namespace MEOV::Window {

Base::Base(std::string_view const title, ImVec2 const& size, bool isClosable, ImGuiWindowFlags flags)
    : _title{ title }
    , _size{ size }
    , _isClosable{ isClosable }
    , _flags{ flags } {}

Base::~Base() {}

void Base::Draw() {
    // ImGui::SetNextWindowSize(_size);  // FIXME: Do smth with window size.
    ImGui::Begin(_title.c_str(), (bool*)_isClosable, _flags.to_ulong());
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

}  // namespace MEOV::Window
