#ifndef BOARD_HPP
#define BOARD_HPP
#include <array>
#include "cell.hpp"

constexpr unsigned short BOARD_WIDTH = 32;
constexpr unsigned short BOARD_HEIGHT = 32;

class board
{
	std::array<std::array<cell, BOARD_WIDTH>, BOARD_HEIGHT> arr; //2d matrix
public:
	board(const board& other) { arr = other.arr; }
	void clearBoard() { arr = {}; }
};

#endif // BOARD_HPP