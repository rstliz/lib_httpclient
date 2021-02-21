cmake_minimum_required(VERSION 3.1)
project(http_client_test CXX)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed.
    Please make a new directory (called a build directory) and run CMake from there.
    You may need to remove CMakeCache.txt." )
endif()


enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(SRC_ROOT_DIR "./")
set(SRC_INCLUDE_DIR ${SRC_ROOT_DIR}/include)
set(APP_MAIN_DIR ${SRC_ROOT_DIR}/main)
set(TEST_DIR ${SRC_ROOT_DIR}/test)
set(LIB_GTESTS gtest gtest_main)

# Library

add_library(http_client SHARED ${APP_MAIN_DIR}/http_client.cpp)
target_include_directories(http_client PRIVATE ${SRC_INCLUDE_DIR})
target_link_libraries(http_client PRIVATE stdc++ curl)


#test execution file

add_executable(http_client_test ${TEST_DIR}/http_client_test.cpp)
target_include_directories(http_client_test PRIVATE ${SRC_INCLUDE_DIR} )
target_link_libraries(http_client_test PRIVATE ${LIB_GTESTS} http_client)
add_test(NAME http_client_test COMMAND $<TARGET_FILE:http_client_test>)
