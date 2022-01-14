#include "board.hpp"
#include "settings.hpp"
#include "menu.hpp"
#include <SFML/Window.hpp>
#include <cmath>

class game
{
	board _board;
	menu _menu;
	// settings are global

public:
	void runLoop()
	{
		auto CELL_WIDTH = settings.WINDOW_WIDTH / static_cast<float>(settings.BOARD_WIDTH); // narrowing conversion from int -> float
		auto CELL_HEIGHT = settings.WINDOW_HEIGHT / static_cast<float>(settings.BOARD_HEIGHT);

		bool rightClickPressed = false; // flag indicating weather to accept mouse inputs (left clicks)
		bool playSelected = false;
		bool optionsSelected = false;

		cell a;
		cell d;
		a.setAlive();
		d.setDead();

		// create the window
		sf::RenderWindow window(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "Game of Life");
		window.setVerticalSyncEnabled(true); // call it once, after creating the window
		window.clear(sf::Color::Black);
		_menu.draw(window);
		window.display();

		while (window.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					// window closed
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						_menu.MoveUp();
						window.clear(sf::Color::Black);
						_menu.draw(window);
						window.display();
						break;

					case sf::Keyboard::Down:
						_menu.MoveDown();
						window.clear(sf::Color::Black);
						_menu.draw(window);
						window.display();
						break;

					case sf::Keyboard::Enter:
						switch (_menu.GetPressedItem())
						{
						case 0:
							std::cout << "Play button has been pressed" << std::endl;
							playSelected = true;
							window.clear(sf::Color::Black);
							window.display();
							break;
						case 1:
						{
							std::cout << "Option button has been pressed" << std::endl;
							window.clear(sf::Color::Black);
							window.display();
							int resolutionWidth;
							int resolutionHeight;
							std::cin >> resolutionWidth >> resolutionHeight;
							// if input values < max resolution
							int numCellsRow;
							int numCellsCol;
							std::cin >> numCellsRow >> numCellsCol;
							if (numCellsRow < resolutionWidth && numCellsCol < resolutionHeight)
							{
								settings.WINDOW_HEIGHT = resolutionHeight;
								settings.WINDOW_WIDTH = resolutionWidth;
								settings.BOARD_HEIGHT = numCellsCol;
								settings.BOARD_WIDTH = numCellsRow;
								CELL_WIDTH = settings.WINDOW_WIDTH / static_cast<float>(settings.BOARD_WIDTH); // recalculating. narrowing conversion from int -> float
								CELL_HEIGHT = settings.WINDOW_HEIGHT / static_cast<float>(settings.BOARD_HEIGHT);
							}

							window.setSize(sf::Vector2u(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT));
							window.display();

							/*board.printBoardArray();
							std::cout << std::endl;*/

							_board = board();

							/*board.printBoardArray();
							std::cout << std::endl;*/

							window.clear(sf::Color::Black);
							puts("window size set");
							playSelected = true;
							sf::View view;
                            sf::Vector2<float> position(0, 0);
                            sf::Vector2<float> size(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT);
                            sf::Rect<float> re(position, size);
                            view.reset(static_cast<const sf::Rect<float> &>(re));

							//view.reset(sf::FloatRect(0, 0, settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT));
							window.setView(view);
							window.display();
							break;
						}
						case 2:
							// Exit selected
							window.close();
							break;

						default:
							break;
						}
						break;
					default:
						break;
					}

					// mouse pressed
				case sf::Event::MouseButtonPressed:
				{
					if (playSelected)
					{
						if (event.mouseButton.button == sf::Mouse::Right)
						{
							std::cout << "the right button was pressed" << std::endl;
							rightClickPressed = !rightClickPressed;
							break;
						}
						else if (event.mouseButton.button == sf::Mouse::Left && !rightClickPressed)
						{
							window.clear(sf::Color::Black);
							window.display();
							std::cout << "the left button was pressed" << std::endl;

							auto n = static_cast<int>(floor(event.mouseButton.x / CELL_WIDTH));
							auto m = static_cast<int>(floor(event.mouseButton.y / CELL_HEIGHT));
							//std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
							//std::cout << i << " " << j << std::endl;
							//std::cout << "cell " << CELL_WIDTH << " " << CELL_HEIGHT;


							//board.printBoardArray();
							//std::cout << std::endl;

							_board.arr[m][n] = a; // the change !!!

							//board.printBoardArray();
							//std::cout << std::endl;

							// draw the cells
							window.clear(sf::Color::Black);

							for (auto i = 0; i < settings.BOARD_HEIGHT; ++i)
							{
								for (auto j = 0; j < settings.BOARD_WIDTH; ++j)
								{
									sf::RectangleShape rectangle(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
									//std::cout << "inside " << CELL_WIDTH << " " << CELL_HEIGHT;

									rectangle.setPosition(sf::Vector2f(CELL_WIDTH * static_cast<float>(j), CELL_HEIGHT * static_cast<float>(i)));
									//std::cout << CELL_WIDTH * static_cast<double>(j) << " " << CELL_HEIGHT * static_cast<double>(i) << " ";
									if (!_board.getCellValue(i, j))
										rectangle.setFillColor(sf::Color(0, 0, 0)); //else it's white by default
									window.draw(rectangle);
								}
							}
							window.display();
							break;
						}
						break;
					}
					break;
				}
				default:
					break;
				}
			}
			// game should be calculating/changing state
			if (rightClickPressed && playSelected)
			{
				_board.applyRulesOnce();
				//std::cout << "applying rules" << std::endl;

				window.clear(sf::Color::Black);

				// draw the cells
				for (auto i = 0; i < settings.BOARD_HEIGHT; ++i)
					for (auto j = 0; j < settings.BOARD_WIDTH; ++j)
					{
						sf::RectangleShape rectangle(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
						rectangle.setPosition(sf::Vector2f(CELL_WIDTH * static_cast<float>(j), CELL_HEIGHT * static_cast<float>(i)));

						if (!_board.getCellValue(i, j)) // if is alive set color black (0, 0, 0)
							rectangle.setFillColor(sf::Color(0, 0, 0)); //else it's white by default
						window.draw(rectangle);
					}
				window.display();
				// end the current frame

			}
		}
	}
};