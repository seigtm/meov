#pragma once

#include "Common.hpp"

namespace MEOV::Window {

class Base {
public:
    Base(std::string_view const title, ImVec2 const& size, bool isClosable = false, ImGuiWindowFlags flags = 0);
    virtual ~Base();

    void Draw();

    void ToggleNoTitleBar();
    void ToggleNoScrollBar();
    void ToggleAlwaysAutoResize();
    void ToggleNoMove();
    void ToggleNoResize();

protected:
    virtual void DrawImpl() = 0;

    std::string _title;
    ImVec2 _size;
    bool _isClosable;
    std::bitset<sizeof(ImGuiWindowFlags)> _flags;

private:
    void ToggleFlag(ImGuiWindowFlags flag);
};

}  // namespace MEOV::Window
