cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -g")
set(TARGET_NAME ReportPrinter)

add_library(${TARGET_NAME} STATIC
  DefaultPrinter.cpp)

target_link_libraries( ${TARGET_NAME} DefaultPrinter.cpp )
