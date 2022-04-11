# === Collecting all sources and headers of external dependencies here. ===#

set(current_dir ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${current_dir}/glm)
add_subdirectory(${current_dir}/sdl)
add_subdirectory(${current_dir}/plog)
set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "Build examples." FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared instead of static libraries." FORCE)
add_subdirectory(${current_dir}/glbinding)
add_subdirectory(${current_dir}/assimp)

#============= ImGui =============#

set(_sources
    # Dear ImGui's common (submodule with docking branch).
        ${current_dir}/imgui/imgui_demo.cpp
        ${current_dir}/imgui/imgui_draw.cpp
        ${current_dir}/imgui/imgui_tables.cpp
        ${current_dir}/imgui/imgui_widgets.cpp
        ${current_dir}/imgui/imgui.cpp

        ${current_dir}/imgui/imconfig.h
        ${current_dir}/imgui/imgui_internal.h
        ${current_dir}/imgui/imgui.h
        ${current_dir}/imgui/imstb_rectpack.h
        ${current_dir}/imgui/imstb_textedit.h
        ${current_dir}/imgui/imstb_truetype.h

    # Dear ImGui's backends (submodule with docking branch).
        ${current_dir}/imgui/backends/imgui_impl_opengl3.cpp
        ${current_dir}/imgui/backends/imgui_impl_sdl.cpp

        ${current_dir}/imgui/backends/imgui_impl_opengl3.h
        ${current_dir}/imgui/backends/imgui_impl_opengl3_loader.h
        ${current_dir}/imgui/backends/imgui_impl_sdl.h

    # Dear ImGui File Dialog (submodule with Lib_Only branch).
        ${current_dir}/imgui_filedialog/ImGuiFileDialog.cpp
        ${current_dir}/imgui_filedialog/ImGuiFileDialog.h
)
add_library(deps_imgui OBJECT ${_sources})
target_include_directories(deps_imgui
    PUBLIC
        ${current_dir}/imgui
        ${current_dir}/imgui_filedialog
)
target_link_libraries(deps_imgui
    PRIVATE
        ${OPENGL_opengl_LIBRARY}
        SDL2::SDL2-static
)
unset(_sources)

#============= STB =============#

set(_sources
        ${current_dir}/stb_image/stb_image.cpp
        ${current_dir}/stb_image/stb_image.h
)
add_library(deps_stb_image OBJECT ${_sources})
target_include_directories(deps_stb_image
    PUBLIC
        ${current_dir}/stb_image
)
unset(_sources)
