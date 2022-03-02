# === Collecting all sources and headers of external dependencies here. ===#

set(deps_sources
    # STB image.
    ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp
    # Dear ImGui's common (submodule with docking branch).
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
    # Dear ImGui's backends (submodule with docking branch).
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl.cpp
    # To make sources visible in the root project's folder.
    PARENT_SCOPE)

set(deps_headers
    # STB image.
    ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.h
    # Dear ImGui's common (submodule with docking branch).
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imconfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_rectpack.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_textedit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_truetype.h
    # Dear ImGui's backends (submodule with docking branch).
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3_loader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl.h
    # To make headers visible in the root project's folder.
    PARENT_SCOPE)
