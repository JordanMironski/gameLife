cmake_minimum_required(VERSION 3.20)

project(gameLife)

set(CMAKE_CXX_STANDARD 20)

add_executable(gameLife src/main.cpp)

# Include the directory where singleton project is. Otherwise, we can't use the
# library

#add_subdirectory(src)
target_include_directories(gameLife PUBLIC src)

# Link the executable and the library together
#target_link_libraries(designpatterns singleton factorymethod abstractfactory builder prototype adapter bridge composite decorator facade)