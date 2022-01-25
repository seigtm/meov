function(make_config_file filename)
    set(SHADER_VERSION_MAJOR 3)
    set(SHADER_VERSION_MINOR 3)
    set(SHADER_VERSION_PATCH 0)
    set(SHADER_VERSION "#version ${SHADER_VERSION_MAJOR}${SHADER_VERSION_MINOR}${SHADER_VERSION_PATCH} core")
    set(PROGRAM_NAME "MEOV | Minimalistic Easy Object Viewer")

    configure_file("${filename}.in" ${filename} @ONLY)
endfunction()