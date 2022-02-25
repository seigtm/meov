#=== Common ===#
cmake_minimum_required(VERSION 3.15)

project(meov LANGUAGES CXX VERSION 0.1.3)

set(target ${CMAKE_PROJECT_NAME})
set(root ${CMAKE_SOURCE_DIR})
set(build_dir ${root}/build)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_INSTALL_PREFIX ${root}/bin/${CMAKE_BUILD_TYPE})
set(install_dir ${CMAKE_INSTALL_PREFIX})

include(${root}/cmake/ConanSetup.cmake)
include(${root}/cmake/GitUtils.cmake)
include(${root}/cmake/ConfigFileMaker.cmake)

grab_git_info(GIT_COMMIT_HASH GIT_COMMIT_DATE GIT_COMMIT_MESSAGE)
message(STATUS "Git: ${GIT_COMMIT_MESSAGE} (${GIT_COMMIT_DATE}) [${GIT_COMMIT_HASH}]")

make_config_file(${root}/src/appinfo/AppInfo.cpp)

#=== Sources ===#
file(GLOB_RECURSE sources ${root}/src/*.c ${root}/src/*.cpp) # CONFIGURE_DEPENDS)
file(GLOB_RECURSE headers ${root}/src/*.h ${root}/src/*.hpp) # CONFIGURE_DEPENDS)

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

conan_setup()
conan_cmake_configure(
    REQUIRES
        sdl/2.0.18
        glbinding/3.1.0
        imgui/1.86
        glm/0.9.9.8
        glew/2.2.0
        plog/1.1.5
    OPTIONS
        sdl:vulkan=False
        sdl:sdl2main=False
    GENERATORS
        cmake_find_package
    IMPORTS
        "bin, *.dll -> ./bin"
        "lib, *.dylib* -> ./bin"
)
conan_cmake_autodetect(settings)
conan_cmake_install(
    PATH_OR_REFERENCE .
    BUILD missing
    REMOTE conancenter
    SETTINGS ${settings}
)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(imgui REQUIRED)
find_package(glbinding REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(plog REQUIRED)

#=== Executable ===#
add_executable(${target} ${sources} ${headers})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${target} PRIVATE DEBUG=1)
endif()
target_include_directories(${target}
    PUBLIC
        ${directories}
)
target_link_libraries(${target}
    PUBLIC
        ${OPENGL_opengl_LIBRARY}
        SDL2::SDL2-static
        imgui::imgui
        glbinding::glbinding
        glm::glm
        GLEW::GLEW
        plog::plog
)
set_target_properties(${target}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        ARCHIVE_OUTPUT_DIRECTORY ${root}/assets
        LIBRARY_OUTPUT_DIRECTORY ${root}/assets
        RUNTIME_OUTPUT_DIRECTORY ${root}/assets
)

#=== Install ===#
install(TARGETS ${target} RUNTIME DESTINATION ${root}/assets)
