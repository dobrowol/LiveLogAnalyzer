cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -g")
set(TARGET_NAME QueueDispatcher)

add_library(${TARGET_NAME} STATIC
  QueueDispatcher.cpp)

include_directories("${CMAKE_SOURCE_DIR}/utils")
include_directories("${CMAKE_SOURCE_DIR}/reportPrinter")

target_link_libraries(${TARGET_NAME} QueueDispatcher.cpp)
