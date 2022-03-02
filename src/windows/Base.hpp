#pragma once

#include "Common.hpp"

namespace meov::Window {

class Base {
public:
    /*!
     * \brief Base window class constuctor.
     * \param title window's title.
     * \param size window's size, (x = 0, y = 0) by default, which means that it will be auto-resized by its contents.
     * \param isClosable should the window be closable, false by default.
     * \param flags Dear ImGui window flags, no flags by default (== 0).
     */
    Base(std::string_view const title, ImVec2 const& size = {}, bool isClosable = false, ImGuiWindowFlags flags = {});
    virtual ~Base() = default;

    //! \brief Draw method. Call it inside your draw loop.
    void Draw();

    //! \brief Toggles Dear ImGui's 'NoTitleBar' flag.
    void ToggleNoTitleBar();
    //! \brief Toggles Dear ImGui's 'NoScrollBar' flag.
    void ToggleNoScrollBar();
    //! \brief Toggles Dear ImGui's 'AlwaysAutoResize' flag.
    void ToggleAlwaysAutoResize();
    //! \brief Toggles Dear ImGui's 'NoMove' flag.
    void ToggleNoMove();
    //! \brief Toggles Dear ImGui's 'NoResize' flag.
    void ToggleNoResize();

protected:
    //! \brief Implementation of draw call inside Dear ImGui's Begin()/End().
    //! Override this with your interface widgets' calls.
    virtual void DrawImpl() = 0;

private:
    /*!
     * \brief Toggles passed Dear ImGui's window flag.
     * \param flag ImGuiWindowsFlag to toggle.
     */
    void ToggleFlag(ImGuiWindowFlags flag);

    std::string _title;
    ImVec2 _size;
    bool _isClosable;
    ImGuiWindowFlags _flags;
};

}  // namespace meov::Window
