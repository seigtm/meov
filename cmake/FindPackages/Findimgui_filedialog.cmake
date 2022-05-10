set(deps_dir ${root}/dependencies)

set(_sources
    ${deps_dir}/imgui_filedialog/ImGuiFileDialog.cpp
)

add_library(deps_imgui_filedialog OBJECT ${_sources})
target_include_directories(deps_imgui_filedialog
    PUBLIC
        ${deps_dir}/imgui
        ${deps_dir}/imgui_filedialog
)

unset(_sources)
