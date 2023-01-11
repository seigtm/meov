cmake_minimum_required(VERSION 3.20)

set(local_root ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE editor_sources ${local_root}/*.c*)
file(GLOB_RECURSE editor_headers ${local_root}/*.h*)

add_library(meov_editor ${editor_sources} ${editor_headers})
add_library(meov::editor ALIAS meov_editor)

set_target_properties(meov_editor PROPERTIES
	CXX_STANDARD ${MEOV_CXX_STANDARD}
    PRECOMPILE_HEADERS_REUSE_FROM precompiled
)
target_include_directories(meov_editor PUBLIC ${include_directories})
target_compile_definitions(meov_editor PUBLIC
    $<$<CONFIG:Debug>:MEOV_DEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)
target_link_libraries(meov_editor PUBLIC meov::core)

unset(local_root)