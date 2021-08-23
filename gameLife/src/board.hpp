#ifndef BOARD_HPP
#define BOARD_HPP
#include <array>
#include <iostream>

#include "cell.hpp"
constexpr unsigned short BOARD_WIDTH = 64;
constexpr unsigned short BOARD_HEIGHT = 64;

struct board
{
	std::array<std::array<cell, BOARD_WIDTH>, BOARD_HEIGHT> arr; //2d matrix
	[[nodiscard]] static bool isSafe(const int& i,const int& j)
	{
		return (i >= 0 && i < BOARD_HEIGHT &&
				j >= 0 && j < BOARD_WIDTH);
	}
	
	//	wheater the value of the cell should change
	bool checkNeighbours(const int& i, const int& j, const bool& value)
	{
		auto aliveCount = 0;

		for (auto ii = i - 1; ii <= i + 1; ++ii)
		{
			for (auto jj = j - 1; jj <= j + 1; ++jj)
			{
				if (ii == i && jj == j) // don't check the cell itself
					continue;
				if (isSafe(ii, jj))
				{
					if (arr[ii][jj].getValue())
						++aliveCount;	// you can break early if any of the counts > 3
					// but since there are are only 8 neighbours no big perfomance gain
				}
			}
		}
		if (value && (aliveCount == 2 || aliveCount == 3)) // rule 1
			return false;
		if (!value && (aliveCount == 3))				   // rule 2
			return true;
		return value; // else change if alive or stay if dead

	}
public:
	void clearBoard() { arr = {}; }

	[[nodiscard]] bool getCellValue(const int& i, const int& j) const
	{
		return arr.at(i).at(j).getValue();
	}
	
	/*
	 *	1. Any live cell with two or three live neighbours survives.
		2. Any dead cell with three live neighbours becomes a live cell.
		3. All other live cells die in the next generation. Similarly, all other dead cells stay dead
	 */
	void applyRulesOnce()
	{
		board nextState;
		
		for (auto i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (auto j = 0; j < BOARD_WIDTH; ++j)
			{
				if (checkNeighbours(i, j, arr[i][j].getValue()))
				{
					if (nextState.arr[i][j].getValue() == arr[i][j].getValue())
						nextState.arr[i][j].change();
				}
				else if (nextState.arr[i][j].getValue() != arr[i][j].getValue())
					nextState.arr[i][j].change();
			}
		}

		*this = nextState; // should be a move
	}
	void printBoardArray() const
	{
		for (const auto& row : arr)
		{
			for (const auto& cell : row)
				std::cout << cell.getValue() << ' ';
			puts("\n");
		}
	}
};

#endif // BOARD_HPP