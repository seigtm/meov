function(make_config_file filename)
    set(SHADER_VERSION_MAJOR 4)
    set(SHADER_VERSION_MINOR 5)
    set(SHADER_VERSION_PATCH 0)
    set(SHADER_VERSION "#version ${SHADER_VERSION_MAJOR}${SHADER_VERSION_MINOR}${SHADER_VERSION_PATCH} core")
    set(PROGRAM_NAME "MEOV | Minimalistic Easy Object Viewer")
    set(LOG_LEVEL ${CMAKE_BUILD_TYPE})

    set(USING_OPENGL true)
    set(USING_VULCAN false)

    configure_file("${filename}.in" ${filename} @ONLY)
endfunction()
