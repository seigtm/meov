cmake_minimum_required(VERSION 3.20)

set(local_root ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE utilities_sources ${local_root}/*.c*)
file(GLOB_RECURSE utilities_headers ${local_root}/*.h*)

add_library(meov_utilities ${utilities_sources} ${utilities_headers})
add_library(meov::utilities ALIAS meov_utilities)

set_target_properties(meov_utilities PROPERTIES
	CXX_STANDARD ${MEOV_CXX_STANDARD}
    PRECOMPILE_HEADERS_REUSE_FROM precompiled
)
target_include_directories(meov_utilities PUBLIC ${include_directories})
target_compile_definitions(meov_utilities PUBLIC
    $<$<CONFIG:Debug>:MEOV_DEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)
target_link_libraries(meov_utilities PUBLIC
    glm::glm
    plog::plog
    deps::imgui
    deps::imgui_filedialog
)

unset(local_root)