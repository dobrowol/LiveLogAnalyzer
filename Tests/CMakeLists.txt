# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/Tests/googletest-src"
                 "${CMAKE_BINARY_DIR}/Tests/googletest-build")

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    message(${gtest_SOURCE_DIR})
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/utils)
include_directories(${CMAKE_SOURCE_DIR}/fileWatcher)
include_directories(${CMAKE_SOURCE_DIR}/queueDispatcher)
add_executable( queueTests queue_test.cpp )
target_link_libraries(queueTests gtest gtest_main)
add_test( NAME queueTests COMMAND queueTests )

add_library(concurrent_queue ${CMAKE_SOURCE_DIR}/utils/concurrent_queue.cpp)
add_executable( fileWatcherTests fileWatcher_tests.cpp)
target_link_libraries(fileWatcherTests gtest gtest_main concurrent_queue)
add_test( NAME fileWatcherTests COMMAND fileWatcherTests )

add_executable( QueueDispatcherTests QueueDispatcher_tests.cpp)
target_link_libraries(QueueDispatcherTests gtest gtest_main gmock concurrent_queue)
add_test( NAME QueueDispatcherTests COMMAND QueueDispatcherTests )
