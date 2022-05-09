#=== Common ===#
cmake_minimum_required(VERSION 3.15)

project(meov LANGUAGES CXX VERSION 0.1.9)

set(target ${CMAKE_PROJECT_NAME})
set(root ${CMAKE_SOURCE_DIR})
set(build_dir ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_INSTALL_PREFIX ${root}/bin)
set(install_dir ${CMAKE_INSTALL_PREFIX})

include(${root}/cmake/git_utils.cmake)
grab_git_info(GIT_COMMIT_HASH GIT_COMMIT_DATE GIT_COMMIT_MESSAGE)
message(STATUS "Git: ${GIT_COMMIT_MESSAGE} (${GIT_COMMIT_DATE}) [${GIT_COMMIT_HASH}]")

include(${root}/cmake/config_file_maker.cmake)
make_config_file(${root}/src/app_info/app_info.cpp)
make_config_file(${root}/src/app_info/definitions.hpp)

#=== Sources ===#
file(GLOB_RECURSE sources ${root}/src/*.c ${root}/src/*.cpp)
file(GLOB_RECURSE headers ${root}/src/*.h ${root}/src/*.hpp)

set(directories)
foreach(header ${headers})
    get_filename_component(directory ${header} PATH)
    list(APPEND directories ${directory})
endforeach()

list(REMOVE_DUPLICATES sources)
list(REMOVE_DUPLICATES headers)
list(REMOVE_DUPLICATES directories)

#=== Dependencies ===#
list(APPEND CMAKE_MODULE_PATH ${build_dir})
list(APPEND CMAKE_PREFIX_PATH ${build_dir})

# Appending sources and headers of dependencies.
add_subdirectory(dependencies)

#=== Executable ===#
add_executable(${target} ${sources} ${headers})
target_include_directories(${target}
    PUBLIC
        ${directories}
)
target_link_libraries(${target}
    PUBLIC
        ${OPENGL_opengl_LIBRARY}
        # Don't really need to include this dep, 'cause we get it from Dear ImGui.
        # SDL2::SDL2-static
        glbinding::glbinding
        glm::glm
        plog::plog
        assimp::assimp
        deps_imgui
        deps_stb_image
    -static
)
set_target_properties(${target}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY ${root}/assets
)

#=== Sanitizer options ===#
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

#=== Clone assets to the build ===#
add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${target}>)

#=== Install ===#
# TODO: Rethink install destination.
# install(TARGETS ${target} RUNTIME DESTINATION ${root}/assets)
