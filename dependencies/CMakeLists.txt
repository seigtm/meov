# Currently processed source directory variable.
set(current_dir ${CMAKE_CURRENT_SOURCE_DIR})

# The function which adds the subdirectory to the build by the given `module_name`
#   and sets two options off.
function(add_dependency module_name)
    if (EXISTS ${current_dir}/${module_name}/CMakeLists.txt)
        message(VERBOSE "Add subdir of ${module_name}")
        set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "Build examples." FORCE)
        set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared instead of static libraries." FORCE)

        add_subdirectory(${current_dir}/${module_name})
    else()
        message(VERBOSE "Looking for ${module_name}")
        find_package(${module_name})
    endif()
endfunction()

# === Collecting all sources of external dependencies here. ===#

add_compile_definitions(HAVE_LIBC)

file(GLOB dirs LIST_DIRECTORIES true ${current_dir}/*)

foreach(directory ${dirs})
    if (IS_DIRECTORY ${directory})
        get_filename_component(module ${directory} NAME)
        add_dependency(${module})
    endif()
endforeach()
