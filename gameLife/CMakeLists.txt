cmake_minimum_required(VERSION 3.20)

project(gameLife)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(externals/SFML)

add_executable(gameLife src/main.cpp)

target_include_directories(gameLife PUBLIC externals/SFML/include)

target_link_libraries(gameLife sfml-window sfml-graphics sfml-system)
target_link_libraries(gameLife archive)

if (WIN32)
    add_custom_command(
        TARGET gameLife POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:gameLife> $<TARGET_FILE_DIR:gameLife>
        COMMAND_EXPAND_LISTS
    )
endif()