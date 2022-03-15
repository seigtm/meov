macro(conan_install)
    # If not multi-config generator (like VS generator).
    set(_options
        sdl:vulkan=False
        sdl:sdl2main=False
    )

    if("${CMAKE_CONFIGURATION_TYPES}" STREQUAL "")
        if(NOT ${CMAKE_GENERATOR} STREQUAL "Ninja")
            list(APPEND _options sdl:iconv=False)
        endif()
    endif()

    conan_cmake_configure(
        REQUIRES
            sdl/2.0.18
            glbinding/3.1.0
            glm/0.9.9.8
            glew/2.2.0
            plog/1.1.5
            assimp/5.1.0
            rapidjson/cci.20211112
        OPTIONS
            ${_options}
        GENERATORS
            cmake_find_package_multi
        IMPORTS
            "bin, *.dll -> ./bin"
            "lib, *.dylib* -> ./bin"
    )

    if("${CMAKE_CONFIGURATION_TYPES}" STREQUAL "")
        conan_cmake_autodetect(settings)
        conan_cmake_install(PATH_OR_REFERENCE .
                            BUILD missing
                            REMOTE conancenter
                            SETTINGS ${settings})
    else()
        foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
            conan_cmake_autodetect(settings BUILD_TYPE ${TYPE})
            conan_cmake_install(PATH_OR_REFERENCE .
                                BUILD missing
                                REMOTE conancenter
                                SETTINGS ${settings})
        endforeach()
    endif()
endmacro()
