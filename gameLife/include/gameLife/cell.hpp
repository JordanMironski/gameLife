#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
	bool value = false;
public:

	[[nodiscard]] bool getValue() const { return value; }
	void setDead() { value = false; }
	void setAlive() { value = true; }
	void change() { value = !value; }
};
#endif // CELL_HPP
