macro(conan_setup)
    # Download automatically, you can also just copy the conan.cmake file.
    if(NOT EXISTS "${build_dir}/conan.cmake")
       message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
       file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${build_dir}/conan.cmake")
    endif()

    include(${build_dir}/conan.cmake)
endmacro()
