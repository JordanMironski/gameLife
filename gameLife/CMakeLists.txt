cmake_minimum_required(VERSION 3.20)

project(gameLife)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-W -Wall)
endif()

add_subdirectory(src)
add_subdirectory(externals/SFML)

#if (WIN32)
#  add_custom_command(
#       TARGET gameLife POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:gameLife> $<TARGET_FILE_DIR:gameLife>
#       COMMAND_EXPAND_LISTS
#    )
#endif()