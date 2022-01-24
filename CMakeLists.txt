#=== Common ===#
cmake_minimum_required(VERSION 3.15)
project(meov LANGUAGES CXX VERSION 0.0.1)

set(target ${CMAKE_PROJECT_NAME})
set(root ${CMAKE_SOURCE_DIR})
set(build_dir ${root}/build)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_INSTALL_PREFIX ${root}/bin/${CMAKE_BUILD_TYPE})
set(install_dir ${CMAKE_INSTALL_PREFIX})

include(${root}/cmake/ConanSetup.cmake)

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

conan_setup()
conan_cmake_configure(
    REQUIRES
        sdl/2.0.18
        glad/0.1.34
        imgui/1.86
        glm/0.9.9.8
        glew/2.2.0
        plog/1.1.5
    OPTIONS
        sdl:vulkan=False
        sdl:sdl2main=False
        glad:gl_version=3.3
        glad:gl_profile=core
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
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(plog REQUIRED)

#=== Executable ===#
add_executable(${target} ${sources} ${headers})
target_include_directories(${target} 
    PUBLIC
        ${directories}
        ${glad_INCLUDES}
)
target_link_libraries(${target}
    PUBLIC
        ${OPENGL_opengl_LIBRARY}
        SDL2::SDL2-static
        imgui::imgui
        glad::glad
        glm::glm
        GLEW::GLEW
        plog::plog
)
set_target_properties(${target}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

#=== Install ===#
install(TARGETS ${target} RUNTIME DESTINATION ${root}/bin)
