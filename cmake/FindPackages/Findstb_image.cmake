set(deps_dir ${root}/dependencies)

set(_sources
    ${deps_dir}/stb_image/stb_image.cpp
)

add_library(deps_stb_image OBJECT ${_sources})
add_library(deps::stb_image ALIAS deps_stb_image)

target_include_directories(deps_stb_image
    PUBLIC
        ${deps_dir}/stb_image
)
unset(_sources)
