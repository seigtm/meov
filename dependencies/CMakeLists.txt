# Currently processed source directory variable.
set(current_dir ${CMAKE_CURRENT_SOURCE_DIR})

# The function which adds the subdirectory to the build by the given `dir`
#   and sets two options off.
function(add_dependency dir)
    set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "Build examples." FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared instead of static libraries." FORCE)

    add_subdirectory(${current_dir}/${dir})
endfunction(add_dep)

# === Collecting all sources of external dependencies here. ===#

add_compile_definitions(HAVE_LIBC)

add_dependency(glm)
add_dependency(sdl)
add_dependency(plog)
add_dependency(glbinding)
add_dependency(assimp)

#============= ImGui =============#

set(_sources
    # Dear ImGui's common (submodule with docking branch).
        ${current_dir}/imgui/imgui_demo.cpp
        ${current_dir}/imgui/imgui_draw.cpp
        ${current_dir}/imgui/imgui_tables.cpp
        ${current_dir}/imgui/imgui_widgets.cpp
        ${current_dir}/imgui/imgui.cpp

    # Dear ImGui's backends (submodule with docking branch).
        ${current_dir}/imgui/backends/imgui_impl_opengl3.cpp
        ${current_dir}/imgui/backends/imgui_impl_sdl.cpp

    # Dear ImGui File Dialog (submodule with Lib_Only branch).
        ${current_dir}/imgui_filedialog/ImGuiFileDialog.cpp
)
add_library(deps_imgui OBJECT ${_sources})
target_include_directories(deps_imgui
    PUBLIC
        ${current_dir}/imgui
        ${current_dir}/imgui_filedialog
)
target_link_libraries(deps_imgui
    PUBLIC
        ${OPENGL_opengl_LIBRARY}
        SDL2::SDL2-static
)
unset(_sources)

#============= STB =============#

set(_sources
        ${current_dir}/stb_image/stb_image.cpp
)
add_library(deps_stb_image OBJECT ${_sources})
target_include_directories(deps_stb_image
    PUBLIC
        ${current_dir}/stb_image
)
unset(_sources)
