#=== Common ===#
cmake_minimum_required(VERSION 3.15)

project(meov LANGUAGES CXX VERSION 0.1.4)

set(target ${CMAKE_PROJECT_NAME})
set(root ${CMAKE_SOURCE_DIR})
set(build_dir ${root}/build)

set(CMAKE_INSTALL_PREFIX ${root}/bin)
set(install_dir ${CMAKE_INSTALL_PREFIX})

include(${root}/cmake/GitUtils.cmake)
grab_git_info(GIT_COMMIT_HASH GIT_COMMIT_DATE GIT_COMMIT_MESSAGE)
message(STATUS "Git: ${GIT_COMMIT_MESSAGE} (${GIT_COMMIT_DATE}) [${GIT_COMMIT_HASH}]")

include(${root}/cmake/ConfigFileMaker.cmake)
make_config_file(${root}/src/appinfo/AppInfo.cpp)

#=== Sources ===#
file(GLOB_RECURSE sources ${root}/src/*.c ${root}/src/*.cpp)
file(GLOB_RECURSE headers ${root}/src/*.h ${root}/src/*.hpp)

# Appending sources and headers of dependencies.
add_subdirectory(dependencies)
list(APPEND headers ${deps_headers})
list(APPEND sources ${deps_sources})

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

include(${root}/cmake/ConanSetup.cmake)
conan_setup()
include(${root}/cmake/ManageDependencies.cmake)
conan_install()

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glbinding REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(plog REQUIRED)
find_package(assimp REQUIRED)

#=== Executable ===#
add_executable(${target} ${sources} ${headers})
target_include_directories(${target}
    PUBLIC
        ${directories}
)
target_link_libraries(${target}
    PUBLIC
        ${OPENGL_opengl_LIBRARY}
        SDL2::SDL2-static
        glbinding::glbinding
        glm::glm
        GLEW::GLEW
        plog::plog
        assimp::assimp
)
set_target_properties(${target}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        # TODO: Rethink output directories (it's bad to assign it to the assets dir).
        # ARCHIVE_OUTPUT_DIRECTORY ${root}/assets
        # LIBRARY_OUTPUT_DIRECTORY ${root}/assets
        # RUNTIME_OUTPUT_DIRECTORY ${root}/assets
)

#=== Sanitizer options ===#
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

#=== Clone assets to the build ===#
add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${target}>)

#=== Install ===#
# TODO: Rethink install destination.
# install(TARGETS ${target} RUNTIME DESTINATION ${root}/assets)
