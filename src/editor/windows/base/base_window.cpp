#include "editor/windows/base/base_window.hpp"

namespace meov::Window {

Base::Base(std::string_view const title, ImVec2 const& size, bool isClosable, ImGuiWindowFlags flags)
    : mTitle{ title }
    , mSize{ size }
    , mIsClosable{ isClosable }
    , mFlags{ flags } {}

void Base::Draw(bool visible) {
    if(!visible)
        return;

    ImGui::SetNextWindowSize(mSize, ImGuiCond_Once);  // Resize will be called once per session.
    ImGui::Begin(mTitle.c_str(), &mIsClosable, mFlags);
    mSize = ImGui::GetWindowSize();
    mPos = ImGui::GetWindowPos();
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

ImVec2 Base::Position() const {
    return mPos;
}
ImVec2 Base::Size() const {
    return mSize;
}

void Base::ToggleFlag(ImGuiWindowFlags flag) {
    mFlags ^= flag;
}

}  // namespace meov::Window
