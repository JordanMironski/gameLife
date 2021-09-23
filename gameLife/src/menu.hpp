#ifndef MENU_HPP
#include <SFML/Graphics.hpp>
#include "settings.hpp"
constexpr unsigned short MAX_NUMBER_OF_ITEMS = 3;

class menu
{
public:
	menu()
	{
		if (!font.loadFromFile("arial.ttf"))
		{
			// handle error
		}

		data[0].setFont(font);
		data[0].setColor(sf::Color::Red);
		data[0].setString("Play");
		data[0].setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1));

		data[1].setFont(font);
		data[1].setColor(sf::Color::White);
		data[1].setString("Options");
		data[1].setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2));

		data[2].setFont(font);
		data[2].setColor(sf::Color::White);
		data[2].setString("Exit");
		data[2].setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 3));

		selectedItemIndex = 0;
	}

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text data[MAX_NUMBER_OF_ITEMS];

};
#endif // MENU_HPP