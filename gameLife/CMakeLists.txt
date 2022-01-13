cmake_minimum_required(VERSION 3.20)

project(gameLife)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_executable(gameLife src/main.cpp)
target_link_libraries(gameLife archive)