cmake_minimum_required(VERSION 3.20)

project(gameLife)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(externals/SFML)

add_executable(gameLife src/main.cpp)


#set_target_properties(gameLife PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/build/)
#set_target_properties(sfml-window PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/build/)
#set_target_properties(sfml-window PROPERTIES CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/build/)
#set_target_properties(sfml-graphics PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/build/)
#set_target_properties(sfml-graphics PROPERTIES CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/build/)


target_include_directories(gameLife PUBLIC externals/SFML/include)

#target_link_libraries(gameLife sfml-window sfml-graphics)
target_link_libraries(gameLife sfml-window sfml-graphics sfml-system Freetype)


#set(BUILD_SHARED_LIBS false)

target_link_libraries(gameLife archive)

set_target_properties(gameLife PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/build/)
#add_custom_command(TARGET sfml-window POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy sfml-graphics.dll ${CMAKE_BINARY_DIR})
add_custom_command(
    TARGET gameLife POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:gameLife> $<TARGET_FILE_DIR:gameLife>
    COMMAND_EXPAND_LISTS
)
#add_custom_command(TARGET gameLife POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy externals/SFML/extlibs/libs-msvc-universal/x64/freetype.lib ${CMAKE_BINARY_DIR})