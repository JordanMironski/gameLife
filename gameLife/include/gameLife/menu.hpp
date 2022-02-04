#ifndef MENU_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <array>
#include "settings.hpp"
constexpr unsigned short MAX_NUMBER_OF_ITEMS = 3;

class menu
{
public:
	menu()
	{
        #ifdef _WIN32
			if (!font.loadFromFile("../../../fonts/arial.ttf"))
			{
				// handle error
				std::cout << "font error\n";
			}
        #endif
        #ifdef linux
			if (!font.loadFromFile("../../fonts/arial.ttf"))
			{
				// handle error
				std::cout << "font error\n";
			}
        #endif

		data[0].setFont(font);
		data[0].setFillColor(sf::Color::Red);
		data[0].setString("Play");
		data[0].setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2.F, settings.WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1.F));

		data[1].setFont(font);
		data[1].setFillColor(sf::Color::White);
		data[1].setString("Options");
		data[1].setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2.F, settings.WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2.F));

		data[2].setFont(font);
		data[2].setFillColor(sf::Color::White);
		data[2].setString("Exit");
		data[2].setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2.F, settings.WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 3.F));

		selectedItemIndex = 0;
	}

	void draw(sf::RenderWindow& window)
	{
		for (auto& el : data)
			window.draw(el);
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
	int GetPressedItem() const { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	std::array<sf::Text, MAX_NUMBER_OF_ITEMS> data;
};
#endif // MENU_HPP