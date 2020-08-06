cmake_minimum_required(VERSION 3.0)
project(SimpleHTTPServer)
project(ServerTest)

include(CTest)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --error-exitcode=1")
set(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/.valgrind-suppressions")

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)


add_executable(ServerTest application.cpp)
add_library(SimpleHTTPServer SHARED  TCP/TCPClient.cpp TCP/TCPClient.h TCP/TCPServer.cpp TCP/TCPServer.h HTTP/HTTPClient.cpp HTTP/HTTPClient.h HTTP/Response.h HTTP/Header.h HTTP/Status.h HTTP/Request.h HTTP/Method.h HTTP/HTTPServer.cpp HTTP/HTTPServer.h)

target_link_libraries (SimpleHTTPServer Threads::Threads)
target_link_libraries(ServerTest SimpleHTTPServer)

