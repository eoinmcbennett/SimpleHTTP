cmake_minimum_required(VERSION 3.0)
project(SimpleHTTPServer)
project(ServerTest)

include(CTest)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --error-exitcode=1")
set(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/.valgrind-suppressions")

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)


add_executable(ServerTest application.cpp )
add_library(SimpleHTTPServer src/net/Socket.cpp src/net/Socket.h src/net/ServerSocket.cpp src/net/ServerSocket.h src/net/HTTPServerSocket.cpp src/net/HTTPServerSocket.h src/net/Connection.cpp src/net/Connection.h src/HTTP/Request.cpp src/HTTP/Request.h src/HTTP/Header.h src/HTTP/Response.cpp src/HTTP/Response.h)

target_link_libraries (SimpleHTTPServer Threads::Threads)
target_link_libraries(ServerTest SimpleHTTPServer)

