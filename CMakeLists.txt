cmake_minimum_required(VERSION 3.5)

project(xredis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(LIBX_INCLUDE_DIR "/home/lx/code/libx/include")
set(LIBX_LIB_DIR "/home/lx/code/libx/build")
set(HIREDIS_INCLUDE_DIR "/home/lx/code/github/hiredis")
set(HIREDIS_LIB_DIR "/home/lx/code/github/hiredis")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${LIBX_INCLUDE_DIR}
    ${HIREDIS_INCLUDE_DIR}
)
file(GLOB_RECURSE LIBXREDIS_SRC_LIST ./src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${LIBXREDIS_SRC_LIST})

target_link_libraries(
    ${PROJECT_NAME}
    ${LIBX_LIB_DIR}/libx.a
    ${HIREDIS_LIB_DIR}/libhiredis.a
)
