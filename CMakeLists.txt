cmake_minimum_required(VERSION 3.7)
project(demo)

set(CMAKE_C_COMPILER "g++")
set(CMAKE_SUPPRESS_REGENERATION 1)
set(CMAKE_USE_RELATIVE_PATHS ON)

SET(BUILD_DIR ./)
#SET(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR}/${CMAKE_BUILD_TYPE})
#MESSAGE(STATUS " output path is ${EXECUTABLE_OUTPUT_PATH}")

aux_source_directory(src SRC_LIST)
aux_source_directory(src/controller SRC_LIST)
aux_source_directory(src/controller/adapter SRC_LIST)
aux_source_directory(src/model SRC_LIST)
aux_source_directory(src/model/window SRC_LIST)
aux_source_directory(src/model/registry SRC_LIST)
aux_source_directory(src/model/entity SRC_LIST)
aux_source_directory(src/model/component SRC_LIST)
aux_source_directory(src/model/component/global SRC_LIST)
aux_source_directory(src/model/system SRC_LIST)
aux_source_directory(src/utils SRC_LIST)
aux_source_directory(src/common SRC_LIST)

include_directories(
	src
	src/controller
	src/controller/adapter
	src/model
	src/model/window
	src/model/registry
	src/model/entity
	src/model/component
	src/model/component/global
	src/model/system
	src/utils
	src/common
	game/superMarioBros
)

add_definitions(-g -std=c++17 -Wall)

# superMarioBros
# aux_source_directory(demo/superMarioBros SRC_LIST)
aux_source_directory(demo/testDemo SRC_LIST)

add_executable(demo ${SRC_LIST} ${OBJ_LIST})
target_link_libraries(demo ncurses)
