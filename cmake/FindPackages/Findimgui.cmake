set(deps_dir ${root}/dependencies)

set(_sources
    # Dear ImGui's common (submodule with docking branch).
        ${deps_dir}/imgui/imgui_demo.cpp
        ${deps_dir}/imgui/imgui_draw.cpp
        ${deps_dir}/imgui/imgui_tables.cpp
        ${deps_dir}/imgui/imgui_widgets.cpp
        ${deps_dir}/imgui/imgui.cpp

    # Dear ImGui's backends (submodule with docking branch).
        ${deps_dir}/imgui/backends/imgui_impl_opengl3.cpp
        ${deps_dir}/imgui/backends/imgui_impl_sdl.cpp

    # Standard library supporting by ImGui
        ${deps_dir}/imgui/misc/cpp/imgui_stdlib.cpp
)

add_library(deps_imgui OBJECT ${_sources})
add_library(deps::imgui ALIAS deps_imgui)

target_include_directories(deps_imgui
    PUBLIC
        ${deps_dir}/imgui
        ${deps_dir}/imgui/misc/cpp
)

target_link_libraries(deps_imgui
    PUBLIC
        ${OPENGL_opengl_LIBRARY}
        SDL2::SDL2-static
)

unset(_sources)
