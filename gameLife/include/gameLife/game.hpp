#include <cmath>
#include <functional>
#include "board.hpp"
#include "menu.hpp"
#include "settings.hpp"
#include "SFML/Window.hpp"

struct StateFactory
{
    std::function<StateFactory(sf::RenderWindow&, Settings& settings)> m_function;
};
StateFactory doGameOfLife(sf::RenderWindow& window, Settings& settings)
{
	std::cout << "Play state" << std::endl;
	bool firstTime = true;
	bool rightClickPressed = false;
	auto board = Board(settings);
	double CELL_WIDTH = settings.WINDOW_WIDTH / static_cast<double>(settings.BOARD_WIDTH);
	double CELL_HEIGHT = settings.WINDOW_HEIGHT / static_cast<double>(settings.BOARD_HEIGHT);
	auto event = sf::Event();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left && !rightClickPressed:
				{
					std::cout << "the left button was pressed" << std::endl;
					auto n = static_cast<int>(floor(event.mouseButton.x / CELL_WIDTH));
					auto m = static_cast<int>(floor(event.mouseButton.y / CELL_HEIGHT));

					board.setAlive(m, n);
					break;
				}
				case sf::Mouse::Right:
				{
					std::cout << "the right button was pressed" << std::endl;
					rightClickPressed = !rightClickPressed;
					break;
				}
				default:
					break;
				}
				break;
			}
			case sf::Event::Closed:
			{
				return {};
			}
			default:
				break;
			}
		}
		//update
		//draw
		if (firstTime)
		{
			window.clear(sf::Color::Black);
			window.display();
			firstTime = false;
		}
		else if (rightClickPressed)
		{
			//std::cout << "rules" << std::endl;
			board.applyRulesOnce();
		}

		// draws the board
		for (auto i = 0; i < settings.BOARD_HEIGHT; ++i)
			for (auto j = 0; j < settings.BOARD_WIDTH; ++j)
			{
				sf::RectangleShape rectangle(static_cast<sf::Vector2f>(sf::Vector2<double>(CELL_WIDTH, CELL_HEIGHT)));
				rectangle.setPosition(sf::Vector2f(CELL_WIDTH * static_cast<float>(j), CELL_HEIGHT * static_cast<float>(i)));
				if (!board.getCellValue(i, j)) // if is dead set color black (0, 0, 0)
					rectangle.setFillColor(sf::Color(0, 0, 0)); //else it's white by default
				window.draw(rectangle);
			}
		window.display();
	}
}

StateFactory doOptions(sf::RenderWindow& window, Settings& settings)
{
	sf::Text text;
	text.setString("Enter resulution & board size in the console");
	
	window.clear(sf::Color::Black);
	window.draw(text);
	window.display();

	int resolutionWidth;
	int resolutionHeight;
	std::cin >> resolutionWidth >> resolutionHeight;
	int numCellsRow;
	int numCellsCol;
	std::cin >> numCellsRow >> numCellsCol;
	// if input values < max resolution
	if (numCellsRow < resolutionWidth && numCellsCol < resolutionHeight)
	{
		settings.WINDOW_HEIGHT = resolutionHeight;
		settings.WINDOW_WIDTH = resolutionWidth;
		settings.BOARD_HEIGHT = numCellsCol;
		settings.BOARD_WIDTH = numCellsRow;
		window.setSize(sf::Vector2<unsigned int>(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT));
	}
	
	sf::View view;
	sf::Vector2<double> position(0, 0);
	sf::Vector2<double> size(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT);
	sf::Rect<float> re(static_cast<sf::Vector2<float>>(position), static_cast<sf::Vector2<float>>(size));
	view.reset(re);
	window.setView(view);

	window.display();
	return { [](sf::RenderWindow& window, Settings& settings) {
										return doGameOfLife(window, settings);
									} }; // go to game state
}


StateFactory doMainMenu(sf::RenderWindow& window, Settings& settings)
{
    std::cout << "Menu state" << std::endl;
    auto menu = Menu(settings); // we can use your `Menu` class as a local variable here.
    bool flag = true;
    while (true)
    {
        // get input
        auto event = sf::Event();
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed: {
                    return {}; // done! return a state factory with no "next state" function
                }
                case sf::Event::KeyPressed:
				{
                    switch (event.key.code) {
                        case sf::Keyboard::Up: {
                            menu.moveUp();
                            flag = true;
                            break;
                        }
                        case sf::Keyboard::Down: {
                            menu.moveDown();
                            flag = true;
                            break;
                        }
                        case sf::Keyboard::Enter: {
                            switch (menu.getPressedItem()) {
                                case 0: // Play
                                {
                                    return {[](sf::RenderWindow &window, Settings &settings) {
                                        return doGameOfLife(window, settings);
                                    }}; // go to game state
                                }
                                case 1: // options
                                {
                                    return {[](sf::RenderWindow &window, Settings &settings) {
                                        return doOptions(window, settings);
                                    }}; // go to options
                                }
                                case 2: {
                                    window.close();
                                    return {};
                                }
                                default:
                                    break;
                            }
                        }
                    }
                }
            }
        }

        // draw the menu
        if (flag) {
            menu.draw(window);
            window.display();
        }
        flag = false;

    }
}