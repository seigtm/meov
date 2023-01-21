set(target ${CMAKE_PROJECT_NAME})
set(build_dir ${CMAKE_CURRENT_BINARY_DIR})
set(install_dir ${CMAKE_INSTALL_PREFIX})
set(root ${CMAKE_SOURCE_DIR})
set(sources_directory ${root}/src)
set(cmake_dir ${root}/cmake)

set(appinfo_path     ${sources_directory}/app_info)
set(editor_directory ${sources_directory}/editor)
set(core_directory   ${sources_directory}/core)
set(utilities_directory ${sources_directory}/utils)
set(dependencies_directory ${root}/dependencies)
set(modules_directory ${sources_directory}/modules)

set(precompiled ${sources_directory}/precompiled.hpp)
set(include_directories ${sources_directory})

set(modules "")
set(definitions "")

set(MEOV_SHADER_VERSION_MAJOR 4)
set(MEOV_SHADER_VERSION_MINOR 5)
set(MEOV_SHADER_VERSION_PATCH 0)
set(MEOV_SHADER_VERSION "#version ${MEOV_SHADER_VERSION_MAJOR}${MEOV_SHADER_VERSION_MINOR}${MEOV_SHADER_VERSION_PATCH} core")
set(MEOV_APP_TITLE "MEOV | Minimalistic Easy Object Viewer")
set(MEOV_LOG_LEVEL ${CMAKE_BUILD_TYPE})

set(MEOV_USING_OPENGL true CACHE BOOL "Use OpenGL")
set(MEOV_USING_VULKAN false CACHE BOOL "Use Vulkan")
set(MEOV_CXX_STANDARD 20 CACHE STRING "C++ Standard")

set(MEOV_BUILD_WITH_EDITOR ON CACHE BOOL "Build with editor")

make_config_file(${appinfo_path}/app_info.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${root}/assets)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${root}/assets)
set(CMAKE_INSTALL_PREFIX ${root}/bin)

list(APPEND CMAKE_MODULE_PATH ${build_dir})
list(APPEND CMAKE_MODULE_PATH ${cmake_dir}/FindPackages)
list(APPEND CMAKE_PREFIX_PATH ${build_dir})

