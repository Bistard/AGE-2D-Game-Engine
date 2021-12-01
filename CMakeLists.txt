cmake_minimum_required(VERSION 3.4)
project(mario)

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
aux_source_directory(src/model/object SRC_LIST)
aux_source_directory(src/view SRC_LIST)
aux_source_directory(src/utils SRC_LIST)
aux_source_directory(src/common SRC_LIST)

# superMarioBros
aux_source_directory(demo/superMarioBros SRC_LIST)

### recursively build the program, but this will build the whole program every time
# file(GLOB_RECURSE SRC_LIST RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")

add_definitions(-g -std=c++14 -Wall)

include_directories(
	src
	src/controller
	src/controller/adapter
	src/model
	src/model/window
	src/model/object
	src/view
	src/utils
	src/common
	game/superMarioBros
)

add_executable(mario ${SRC_LIST} ${OBJ_LIST})
target_link_libraries(mario ncurses) #  clntsh ociei occi hiredis_vip protobuf
