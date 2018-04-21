cmake_minimum_required(VERSION 3.10)
project(telnet_menu)

set(CMAKE_CXX_STANDARD 17)

add_executable(server src/main.cpp src/server/server.cpp src/server/server.h src/server/logger.h src/server/connection.cpp src/server/connection.h src/server/connection_exception.h src/server/connection_exception.cpp)