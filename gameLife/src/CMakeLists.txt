cmake_minimum_required(VERSION 3.20)

add_library(archive INTERFACE board.hpp cell.hpp game.hpp menu.hpp settings.hpp)
set_target_properties(archive PROPERTIES LINKER_LANGUAGE CXX)