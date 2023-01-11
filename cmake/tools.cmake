macro(add_precompiled_target name)
	add_library(${name} STATIC ${sources_directory}/${name}.cpp)
	target_precompile_headers(precompiled PUBLIC ${sources_directory}/${name}.hpp)
	set_target_properties(${name} PROPERTIES
		CXX_STANDARD ${MEOV_CXX_STANDARD}
	)
	target_link_libraries(${name} PUBLIC
		${OPENGL_opengl_LIBRARY}
		glbinding::glbinding
		glm::glm
		plog::plog
		deps::imgui
		deps::imgui_filedialog
		deps::stb_image
	)
endmacro()

macro(add_module dir module_name)
	if(NOT EXISTS ${dir}/CMakeLists.txt)
		return()
	endif()

	add_subdirectory(${dir})
	if(TARGET ${module_name})
		list(APPEND modules ${module_name})
	else()
		message(WARNING "Cannot add ${module_name} module!")
	endif()
endmacro(add_module)

macro(set_bool value name)
    if(${value})
        set(${name} true)
    else()
        set(${name} false)
    endif()
endmacro()

function(make_config_file filename)
    set_bool(MEOV_BUILD_WITH_EDITOR var_build_with_editor)
    set_bool(MEOV_USING_OPENGL var_using_opengl)
    set_bool(MEOV_USING_VULKAN var_using_vulkan)

    configure_file("${filename}.in" ${filename} NEWLINE_STYLE LF @ONLY)
endfunction()
