cmake_minimum_required(VERSION 3.20)

set(local_root ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE core_sources ${local_root}/*.c*)
file(GLOB_RECURSE core_headers ${local_root}/*.h*)

add_library(meov_core ${core_sources} ${core_headers})
add_library(meov::core ALIAS meov_core)

set_target_properties(meov_core PROPERTIES
	CXX_STANDARD ${MEOV_CXX_STANDARD}
    PRECOMPILE_HEADERS_REUSE_FROM precompiled
)
target_include_directories(meov_core PUBLIC ${include_directories})
target_compile_definitions(meov_core PUBLIC
    $<$<CONFIG:Debug>:MEOV_DEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)
target_link_libraries(meov_core PUBLIC
    meov::utilities
    ${OPENGL_opengl_LIBRARY}

    # Don't really need to include this dep, 'cause we get it from Dear ImGui.
    # SDL2::SDL2-static
    glbinding::glbinding
    assimp::assimp
    deps::stb_image
    -static
)

unset(local_root)