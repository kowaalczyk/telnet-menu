cmake_minimum_required(VERSION 3.10)
project(telnet_menu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pedantic -Wall -Wextra -Werror")

add_executable(server src/main.cpp src/server/listener.cpp src/server/listener.h src/server/logger.h src/server/connection.cpp src/server/connection.h src/server/connection_exception.h src/server/connection_exception.cpp src/server/menu.cpp src/server/menu.h src/server/menu_exception.cpp src/server/menu_exception.h src/server/io.h src/server/key.h src/server/io_exception.cpp src/server/io_exception.h src/server/io.cpp)