#ifndef BOARD_HPP
#define BOARD_HPP
#include <vector>
#include <iostream>

#include "settings.hpp"

class Board
{
	friend class Game;
	Settings* settings;
	std::vector<std::vector<bool>> arr;

private:
	//	whether the value of the cell should change
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
					if (arr[ii][jj])
						++aliveCount;	// you can break early if > 3
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
	Board(Settings* settings) : settings(settings), arr(std::vector<std::vector<bool>>(settings->BOARD_HEIGHT, std::vector<bool>(settings->BOARD_WIDTH, false)))
	{}

	void clearBoard() { arr = {}; }

	bool getCellValue(const int& i, const int& j) const
	{
		return arr.at(i).at(j);
	}

	/*
	 *	1. Any live cell with two or three live neighbours survives.
		2. Any dead cell with three live neighbours becomes a live cell.
		3. All other alive cells die in the next generation. Similarly, all other dead cells stay dead
	 */
	void applyRulesOnce()
	{
		Board nextState(settings);

		for (auto i = 0; i < settings->BOARD_HEIGHT; ++i)
		{
			for (auto j = 0; j < settings->BOARD_WIDTH; ++j)
			{
				if (checkNeighbours(i, j, arr[i][j]))
				{
					if (nextState.arr[i][j] == arr[i][j])
						nextState.arr[i][j] = !nextState.arr[i][j];
				}
				else if (nextState.arr[i][j] != arr[i][j])
					nextState.arr[i][j] = !nextState.arr[i][j];
			}
		}

		*this = std::move(nextState); // should be a move
	}

    bool isSafe(const int& i, const int& j)
    {
        return (i >= 0 && i < settings->BOARD_HEIGHT &&
                j >= 0 && j < settings->BOARD_WIDTH);
    }

	void printBoardArray() const
	{
		for (const auto& row : arr)
		{
			for (const auto& cell : row)
				std::cout << cell << ' ';
			puts("\n");
		}
	}
};
#endif // BOARD_HPP