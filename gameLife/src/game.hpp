#include "board.hpp"
#include "settings.hpp"
#include "menu.hpp"

#include <Windows.h>

class game
{
    //friend class board;
	board board;
	menu menu;
	// settings are global
public:
	void runLoop()
	{
        //board board();
        
        //this->board = class board();
        float CELL_WIDTH = settings.WINDOW_WIDTH / static_cast<float>(settings.BOARD_WIDTH); // narrowing conversion from int -> float
        float CELL_HEIGHT = settings.WINDOW_HEIGHT / static_cast<float>(settings.BOARD_HEIGHT);

        bool rightClickPressed = false; // flag indicating weather to accept mouse inputs (left clicks)
        bool playSelected = false;
        bool optionsSelected = false;

        cell a;
        cell d;
        a.setAlive();
        d.setDead();

        //std::vector<std::vector<cell>> init(settings.BOARD_HEIGHT, std::vector<cell>(settings.BOARD_WIDTH, d)); // i want this not to be here

        //board board(init);
        /*board board;
        menu menu;*/

        // create the window
        sf::RenderWindow window(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "Game of Life");
        window.setVerticalSyncEnabled(true); // call it once, after creating the window
        window.clear(sf::Color::Black);
        menu.draw(window);
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
                        menu.MoveUp();
                        window.clear(sf::Color::Black);
                        menu.draw(window);
                        window.display();
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        window.clear(sf::Color::Black);
                        menu.draw(window);
                        window.display();
                        break;

                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            std::cout << "Play button has been pressed" << std::endl;
                            playSelected = true;
                            window.clear(sf::Color::Black);
                            window.display();
                            break;
                        case 1:
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
                            }
                            window.setSize(sf::Vector2u(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT));

                            //board = class board();
                            window.clear(sf::Color::Black);
                            puts("window size set");
                            playSelected = true;
                            window.display();
                            break;
                        case 2:
                            window.close();
                            break;
                        }
                        break;
                    }
                    // mouse pressed
                    if (playSelected)
                    {
                        //class board temp = board;
                        case sf::Event::MouseButtonPressed:
                            if (event.mouseButton.button == sf::Mouse::Right)
                            {
                                std::cout << "the right button was pressed" << std::endl;
                                rightClickPressed = !rightClickPressed;
                                break;
                            }
                            if (event.mouseButton.button == sf::Mouse::Left && !rightClickPressed)
                            {
                                window.clear(sf::Color::Black);
                                window.display();
                                std::cout << "the left button was pressed" << std::endl;

                                auto j = static_cast<int>(floor(event.mouseButton.x / CELL_WIDTH));
                                auto i = static_cast<int>(floor(event.mouseButton.y / CELL_HEIGHT));
                                std::cout << i << " " << j << std::endl;

                                board.printBoardArray();
                                std::cout << std::endl;

                                board.arr[i][j] = a; // the change
                                
                                board.printBoardArray();
                                std::cout << std::endl;
                                // draw the cells
                                window.clear(sf::Color::Black);


                                for (auto i = 0; i < settings.BOARD_HEIGHT; ++i)
                                    for (auto j = 0; j < settings.BOARD_WIDTH; ++j)
                                    {
                                        sf::RectangleShape rectangle(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
                                        rectangle.setPosition(CELL_WIDTH * static_cast<float>(j), CELL_HEIGHT * static_cast<float>(i));

                                        if (!board.arr[i][j].getValue()) // if is alive set color black (0, 0, 0)
                                            rectangle.setFillColor(sf::Color(0, 0, 0)); //else it's white by default
                                        window.draw(rectangle);
                                    }
                                window.display();
                                //Sleep(5000);
                                break;
                            }
                            //break;
                        }

                    // we don't process other types of events
                    default:
                        break;
                }
            }
            // game should be calculating/changing state
            if (rightClickPressed && playSelected)
            {
                window.clear(sf::Color::Black);

                // draw the cells
                for (auto i = 0; i < settings.BOARD_HEIGHT; ++i)
                    for (auto j = 0; j < settings.BOARD_WIDTH; ++j)
                    {
                        sf::RectangleShape rectangle(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
                        rectangle.setPosition((CELL_WIDTH) * static_cast<float>(j), CELL_HEIGHT * static_cast<float>(i));

                        if (!board.getCellValue(i, j)) // if is alive set color black (0, 0, 0)
                            rectangle.setFillColor(sf::Color(0, 0, 0)); //else it's white by default
                        window.draw(rectangle);
                    }

                // end the current frame
                std::cout << "applying rules" << std::endl;
                window.display();
                board.applyRulesOnce();

                //break;
            }
        }
	}
};