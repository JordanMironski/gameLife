cmake_minimum_required(VERSION 3.20)

file(GLOB HEADER_LIST ${PROJECT_SOURCE_DIR}/include/gameLife/*.hpp)

add_executable(gameLife main.cpp ${HEADER_LIST})
set_target_properties(gameLife PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_include_directories(gameLife PRIVATE externals/SFML/include)
target_include_directories(gameLife PUBLIC  ${PROJECT_SOURCE_DIR}/include/gameLife)

target_link_libraries(gameLife PRIVATE sfml-window sfml-graphics sfml-system)
