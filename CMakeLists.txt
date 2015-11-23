cmake_minimum_required(VERSION 2.6)

project(sandbox)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(POLYCODE_FRAMEWORK_ROOT "/home/fzort/projects/Polycode/Release/Linux/Framework")

include_directories(
	${OPENGL_INCLUDE_DIR}
	${SDL_INCLUDE_DIR}
	${POLYCODE_FRAMEWORK_ROOT}/Core/include
	${POLYCODE_FRAMEWORK_ROOT}/Core/Dependencies/include
	${POLYCODE_FRAMEWORK_ROOT}/Core/Dependencies/include/AL)

link_directories(
	${POLYCODE_FRAMEWORK_ROOT}/Core/lib
	${POLYCODE_FRAMEWORK_ROOT}/Core/Dependencies/lib)

set(POLYCODE_LIBRARIES
	Polycore_d
	png
	z
	openal
	libvorbisfile
	libvorbis
	libogg
	physfs
	freetype)

add_subdirectory(ghost)
add_subdirectory(circles)
