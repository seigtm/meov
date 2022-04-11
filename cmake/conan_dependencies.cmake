macro(conan_install)
    conan_cmake_configure(
        REQUIRES
            plog/1.1.5
            assimp/5.1.0
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
