cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -g")
include_directories("${CMAKE_SOURCE_DIR}/utils")
set(TARGET_NAME fileWatcher)

add_library(${TARGET_NAME} STATIC
  fileWatcher.cpp)

target_include_directories(${TARGET_NAME}
  INTERFACE "${CMAKE_SOURCE_DIR}/utils")

target_link_libraries( fileWatcher fileWatcher.cpp )
