macro(conan_install)
    # If not multi-config generator (like VS generator).
    if("${CMAKE_CONFIGURATION_TYPES}" STREQUAL "")
        conan_cmake_configure(
            REQUIRES
                sdl/2.0.18
                glbinding/3.1.0
                glm/0.9.9.8
                glew/2.2.0
                plog/1.1.5
                assimp/5.1.0
            OPTIONS
                sdl:vulkan=False
                sdl:sdl2main=False
                sdl:iconv=False
            GENERATORS
                cmake_find_package_multi
            IMPORTS
                "bin, *.dll -> ./bin"
                "lib, *.dylib* -> ./bin"
        )
        conan_cmake_autodetect(settings)
        conan_cmake_install(PATH_OR_REFERENCE .
                            BUILD missing
                            REMOTE conancenter
                            SETTINGS ${settings})
    else()
        conan_cmake_configure(
            REQUIRES
                sdl/2.0.18
                glbinding/3.1.0
                glm/0.9.9.8
                glew/2.2.0
                plog/1.1.5
                assimp/5.1.0
            OPTIONS
                sdl:vulkan=False
                sdl:sdl2main=False
            GENERATORS
                cmake_find_package_multi
            IMPORTS
                "bin, *.dll -> ./bin"
                "lib, *.dylib* -> ./bin"
        )
        foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
            conan_cmake_autodetect(settings BUILD_TYPE ${TYPE})
            conan_cmake_install(PATH_OR_REFERENCE .
                                BUILD missing
                                REMOTE conancenter
                                SETTINGS ${settings})
        endforeach()
    endif()
endmacro()
