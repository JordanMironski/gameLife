#ifndef MENU_HPP
#include <array>
#include <iostream>

#include "settings.hpp"
#include "SFML/Graphics.hpp"
constexpr int MAX_NUMBER_OF_ITEMS = 3;

class Menu
{
public:
	Menu(Settings* settings)
	{
        if (!font.loadFromFile("../../../fonts/arial.ttf"))
        {
            std::cout << "font error\n";
        }
		data[0].setFont(font);
		data[0].setFillColor(sf::Color::Red);
		data[0].setString("Play");
		data[0].setPosition(sf::Vector2f(settings->WINDOW_WIDTH / 2.F, settings->WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1.F));

		data[1].setFont(font);
		data[1].setFillColor(sf::Color::White);
		data[1].setString("Options");
		data[1].setPosition(sf::Vector2f(settings->WINDOW_WIDTH / 2.F, settings->WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2.F));

		data[2].setFont(font);
		data[2].setFillColor(sf::Color::White);
		data[2].setString("Exit");
		data[2].setPosition(sf::Vector2f(settings->WINDOW_WIDTH / 2.F, settings->WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 3.F));

		selectedItemIndex = 0;
	}

	void draw(sf::RenderWindow& window)
	{
		for (auto& el : data)
			window.draw(el);
	}
	void moveUp()
	{
		if (selectedItemIndex - 1 >= 0)
		{
			data[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			data[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	void moveDown()
	{
		if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
		{
			data[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			data[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	int getPressedItem() const { return selectedItemIndex; }

private:
	sf::Font font;
	std::array<sf::Text, MAX_NUMBER_OF_ITEMS> data;
    int selectedItemIndex;
};
#endif // MENU_HPP