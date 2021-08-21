#ifndef CELL_HPP
#define CELL_HPP

class cell
{
	bool value = false;
public:
	[[nodiscard]] bool isDead() const { return value == false; }
	[[nodiscard]] bool isAlice() const { return value == true; }
	
	void setDead() { value = false; }
	void setAlive() { value = true; }
	void change() { value = !value; }
};
#endif // CELL_HPP
