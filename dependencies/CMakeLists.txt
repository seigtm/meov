# Currently processed source directory variable.
set(current_dir ${CMAKE_CURRENT_SOURCE_DIR})

# The function which adds the subdirectory to the build by the given `dir`
#   and sets two options off.
function(add_dependency dir)
    set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "Build examples." FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared instead of static libraries." FORCE)

    add_subdirectory(${current_dir}/${dir})
endfunction(add_dep)

# === Collecting all sources of external dependencies here. ===#

add_compile_definitions(HAVE_LIBC)

add_dependency(glm)
add_dependency(sdl)
add_dependency(plog)
add_dependency(glbinding)
add_dependency(assimp)

#============= ImGui =============#

find_package(ImGui)

#============= STB =============#

find_package(STBImage)