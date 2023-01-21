cmake_minimum_required(VERSION 3.20)

set(local_root ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB directories LIST_DIRECTORIES true ${local_root}/*)

set(modules_sources "")
foreach(directory IN LISTS directories)
	if(NOT IS_DIRECTORY ${directory})
		continue()
	endif()
	string(REPLACE ${local_root}/ "" module ${directory})
	message(STATUS "Load module: ${module}")

	file(GLOB_RECURSE ${module}_sources ${directory}/*.h** ${directory}/*.c**)
	list(APPEND modules_sources ${${module}_sources})
endforeach()

add_library(meov_modules STATIC ${modules_sources})
add_library(meov::modules ALIAS meov_modules)

target_include_directories(meov_modules PUBLIC ${local_root})
set_target_properties(meov_modules PROPERTIES
    CXX_STANDARD ${MEOV_CXX_STANDARD}
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${root}/assets
)
