cmake_minimum_required(VERSION 3.20)

file(GLOB HEADER_LIST ${PROJECT_SOURCE_DIR}/include/gameLife/*.hpp)

add_executable(gameLife main.cpp ${HEADER_LIST})
set_target_properties(gameLife PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_include_directories(gameLife PRIVATE externals/SFML/include)
target_include_directories(gameLife PUBLIC  ${PROJECT_SOURCE_DIR}/include/gameLife)

target_link_libraries(gameLife PRIVATE sfml-window sfml-graphics sfml-system)

if (WIN32)
  add_custom_command(
       TARGET gameLife POST_BUILD
       COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:gameLife> $<TARGET_FILE_DIR:gameLife>
       COMMAND_EXPAND_LISTS
    )
endif()