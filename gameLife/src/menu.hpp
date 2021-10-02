#ifndef MENU_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "settings.hpp"
constexpr size_t MAX_NUMBER_OF_ITEMS = 3;

class menu
{
public:
	menu()
	{
		if (!font.loadFromFile("fonts\\arial.ttf"))
		{
			// handle error
			std::cout << "font error\n";
		}

		data[0].setFont(font);
		data[0].setFillColor(sf::Color::Red);
		data[0].setString("Play");
		data[0].setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1));

		data[1].setFont(font);
		data[1].setFillColor(sf::Color::White);
		data[1].setString("Options");
		data[1].setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2));

		data[2].setFont(font);
		data[2].setFillColor(sf::Color::White);
		data[2].setString("Exit");
		data[2].setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 3));

		selectedItemIndex = 0;
	}

	void draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
			window.draw(data[i]);
	}
	void MoveUp()
	{
		if (selectedItemIndex - 1 >= 0)
		{
			data[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			data[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	void MoveDown()
	{
		if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
		{
			data[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			data[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text data[MAX_NUMBER_OF_ITEMS];
};
#endif // MENU_HPP