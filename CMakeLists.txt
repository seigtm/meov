# === Common ===#
cmake_minimum_required(VERSION 3.20)

include(cmake/tools.cmake)
project(meov
    VERSION 0.2.8
    LANGUAGES CXX
)
include(cmake/options.cmake)

add_precompiled_target(precompiled)

# === Dependencies ===#
add_subdirectory(${dependencies_directory})
add_module(${modules_directory} meov::modules)
add_module(${utilities_directory} meov::utilities)
add_module(${core_directory} meov::core)

if(MEOV_BUILD_WITH_EDITOR)
    add_module(${editor_directory} meov::editor)
    list(APPEND definitions MEOV_WITH_EDITOR)
endif()

# === Executable ===#
add_executable(${target} ${sources_directory}/main.cpp)

set_target_properties(${target} PROPERTIES
    CXX_STANDARD ${MEOV_CXX_STANDARD}
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY ${root}/assets
    PRECOMPILE_HEADERS_REUSE_FROM precompiled
)
target_compile_definitions(${target} PUBLIC
    $<$<CONFIG:Debug>:MEOV_DEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
    ${definitions}
)
target_link_libraries(${target} PUBLIC
    ${modules}

    glbinding::glbinding
)

# === Sanitizer options ===#
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# === Clone assets to the build ===#
add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${target}>
)

# === Install ===#
# TODO: Rethink install destination.
# install(TARGETS ${target} RUNTIME DESTINATION ${root}/assets)
