cmake_minimum_required(VERSION 3.20)
project(LSDetris)

# activate toolchain file to enable search via find_package()
# TODO : this shit doesn't seem to work when I set toolchain file from cmake script
set(VCPKG_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_TOOLCHAIN_FILE} CACHE FILEPATH "path to vcpkg toolchain file")
# TODO : ...but this shit seems to work when I force its inclusion
# include(${VCPKG_TOOLCHAIN_FILE})

# variable from vcpkg.cmake toolchain file
# this directory will contain all installed <Package>Config.cmake files
# this is required for find_package()
set(VCPKG_ALL_INSTALLED_DIR ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET})
message(STATUS ${VCPKG_ALL_INSTALLED_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${VCPKG_ALL_INSTALLED_DIR})
message(STATUS ${CMAKE_MODULE_PATH})

# opengl dependencies
if(WIN32 OR (UNIX AND NOT APPLE))
	find_package(OpenGL REQUIRED)
	set(OPENGL_LIBS OpenGL::GL)
else()
	message(FATAL_ERROR "System unsupported")
endif()

# vcpkg dependencies
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${VCPKG_ALL_INSTALLED_DIR})
message(STATUS ${CMAKE_PREFIX_PATH})

find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED) # yeah, installed by vcpkg

set(ALL_DEPS "${OPENGL_LIBS};glfw;GLEW::GLEW;EnTT::EnTT;glm::glm;OpenAL::OpenAL")

# utility to create neat project filters
# takes one optional parameter - source directory that is current directory (.) by default
# globs all files in a directory and provides filter tree
function(populate_filters)
	if(DEFINED ARGV0)
		set(src_dir ${ARGV0})
	else()
		set(src_dir .)
	endif()
	if(MSVC_IDE)
		file(GLOB_RECURSE files LIST_DIRECTORIES false
			${src_dir}/*.cpp ${src_dir}/*.hpp
			${src_dir}/*.c ${src_dir}/*.h)
		source_group(TREE ${src_dir} FILES ${files})
	endif()
endfunction()

# projects
add_subdirectory(src)