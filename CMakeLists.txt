cmake_minimum_required(VERSION 3.20)
project(LSDetris)

include(ExternalProject)

# external folder
set(EXTERNAL_PREFIX "external")

# vcpkg variables
# TODO : rename all vars (except VCPKG_TARGET_TRIPLET) as VCPKG_ prefix is used by vcpkg itself
set(VCPKG_PREFIX "${EXTERNAL_PREFIX}/vcpkg")
set(VCPKG_SOURCE_DIR "${VCPKG_PREFIX}/src/vcpkg")
set(VCPKG_REPOSITORY "https://github.com/microsoft/vcpkg")
set(VCPKG_REPOSITORY_TAG "2022.05.10")
set(VCPKG_SHOW_PROGRESS ON)
set(VCPKG_BUILD_DIR ${CMAKE_BINARY_DIR}/${VCPKG_SOURCE_DIR})
set(VCPKG_CMD ${VCPKG_BUILD_DIR}/vcpkg)

if(WIN32)
	set(VCPKG_CONFIGURE_CMD "${VCPKG_BUILD_DIR}/bootstrap-vcpkg.bat")
	set(VCPKG_PLATFORM "windows")
	set(VCPKG_TARGET_TRIPLET "x64-windows") # set vcpkg variable
elseif(UNIX AND NOT APPLE)
	set(VCPKG_CONFIGURE_CMD "${VCPKG_BUILD_DIR}/bootstrap-vcpkg.sh")
	set(VCPKG_PLATFORM "linux")
	set(VCPKG_TARGET_TRIPLET "x64-linux") # set vcpkg variable
else()
	message(FATAL_ERROR "System unsupported")
endif()

set(VCPKG_TOOLCHAIN_FILE "${VCPKG_BUILD_DIR}/scripts/buildsystems/vcpkg.cmake")
#set(CMAKE_TOOLCHAIN_FILE ${VCPKG_TOOLCHAIN_FILE} CACHE FILEPATH "path to vcpkg toolchain file")

# install vcpkg via ExternalProject
ExternalProject_Add(vcpkg
	PREFIX ${VCPKG_PREFIX}
	GIT_REPOSITORY ${VCPKG_REPOSITORY}
	GIT_TAG ${VCPKG_REPOSITORY_TAG}
	GIT_PROGRESS ${VCPKG_SHOW_PROGRESS}
	UPDATE_COMMAND "" # so it doesn't install itself each build (and we don't need any updates)
	CONFIGURE_COMMAND ${VCPKG_CONFIGURE_CMD}
	BUILD_COMMAND ""
	INSTALL_COMMAND "")

# download & install all vcpkg-managed dependencies
set(VCPKG_PACKAGES "glew;glfw3;entt;openal-soft;glm")
foreach(dep ${VCPKG_PACKAGES})
	ExternalProject_Add_Step(vcpkg vcpkg-${dep}
		COMMAND ${VCPKG_CMD} install ${dep} "--triplet=${VCPKG_TARGET_TRIPLET}")
endforeach()

# I don't know if I do it the right way
# activate toolchain file to enable search via find_package()
include(${VCPKG_TOOLCHAIN_FILE})
# variable from vcpkg.cmake toolchain file
# this directory will contain all installed <Package>Config.cmake files
# this is required for find_package()
set(VCPKG_ALL_INSTALLED_DIR ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${VCPKG_ALL_INSTALLED_DIR})

# opengl dependencies
if(WIN32)
	find_package(OpenGL REQUIRED)
	set(OPENGL_LIBS OpenGL::GL)
elseif(UNIX AND NOT APPLE)
	# TODO : linux specific stuff
	message(FATAL_ERROR "OpenGL for linux will be a little bit later...")
	set(OPENGL_LIBS "")
else()
	message(FATAL_ERROR "System unsupported")
endif()

# vcpkg dependencies
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${VCPKG_ALL_INSTALLED_DIR})
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED) # yeah, installed by vcpkg

set(ALL_DEPS "${OPENGL_LIBS};glfw;GLEW::glew;EnTT::EnTT;glm::glm;OpenAL::OpenAL")

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