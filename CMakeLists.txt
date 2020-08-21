cmake_minimum_required(VERSION 3.0)
project(SimpleHTTPServer)
project(ServerTest)

include(CTest)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --error-exitcode=1")
set(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/.valgrind-suppressions")

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)

file(GLOB_RECURSE SOURCEFILES src/
        "*.h"
        "*.cpp"
        )

add_executable(ServerTest application.cpp )
add_library(SimpleHTTPServer ${SOURCEFILES})

target_link_libraries (SimpleHTTPServer Threads::Threads)
target_link_libraries(ServerTest SimpleHTTPServer)

