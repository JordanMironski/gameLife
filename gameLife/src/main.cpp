#include "board.hpp"
#include "settings.hpp"
#include "menu.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
//extern constexpr unsigned short WINDOW_WIDTH = 800;
//extern constexpr unsigned short WINDOW_HEIGHT = 800;

int main()
{
    float CELL_WIDTH = static_cast<float>(settings.WINDOW_WIDTH) / settings.BOARD_WIDTH;
    float CELL_HEIGHT = static_cast<float>(settings.WINDOW_HEIGHT) / settings.BOARD_HEIGHT;
    bool rightClickOn = false; // flag indicating weather to accept mouse inputs (left clicks)
    //std::array<std::array<cell, settings.BOARD_WIDTH>, settings.BOARD_HEIGHT> init;
    cell a;
    cell d;
    a.setAlive();
    d.setDead();
    //std::vector<std::vector<cell>> init;
    //std::vector<cell> forInit(settings.BOARD_WIDTH, d);
    //std::vector<std::vector<cell>> init(settings.BOARD_HEIGHT, forInit);

    std::vector<std::vector<cell>> init(settings.BOARD_HEIGHT, std::vector<cell>(settings.BOARD_WIDTH, d));


    //init.resize(settings.)
    //init[0] = { d,d,a };
    //init[1] = { a,d,a };
    //init[2] = { d,a,a };
    
    board board(init);
    menu menu;
    /*for (const auto& row : init)
    {
        for (const auto& el : row)
            std::cout << el.getValue() << " ";
        std::cout << std::endl;
    }*/
    /*board.arr[0] = { a,a,d };
    board.arr[1] = { a,a,d };
    board.arr[2] = { d,d,d };
	*/
    //board.printBoardArray();
    // create the window
    sf::RenderWindow window(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "Game of Life");
    window.setVerticalSyncEnabled(true); // call it once, after creating the window
    //window.setFramerateLimit(8);
    window.clear(sf::Color::Black);
    menu.draw(window);
    window.display();
    // run the program as long as the window is open
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
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;

                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                            case 0:
                                std::cout << "Play button has been pressed" << std::endl;
                                break;
                            case 1:
                                std::cout << "Option button has been pressed" << std::endl;
                                break;
                            case 2:
                                window.close();
                                break;
                        }

                        break;
                }
            // mouse pressed
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    rightClickOn = !rightClickOn;
                    board = init;
                    break;
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;

                    auto j = static_cast<int>(floor(event.mouseButton.x / CELL_WIDTH));
                    auto i = static_cast<int>(floor(event.mouseButton.y / CELL_HEIGHT));
                    std::cout << i << " " << j << std::endl;
                    init[i][j] = a;
                    window.clear(sf::Color::Black);
                    // draw the cells
                    for (auto i = 0; i < settings.BOARD_HEIGHT; ++i)
                        for (auto j = 0; j < settings.BOARD_WIDTH; ++j)
                        {
                            sf::RectangleShape rectangle(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
                            rectangle.setPosition((CELL_WIDTH) * static_cast<float>(j), CELL_HEIGHT * static_cast<float>(i));

                            if (!init[i][j].getValue()) // if is alive set color black (0, 0, 0)
                                rectangle.setFillColor(sf::Color(0, 0, 0)); //else it's white by default
                            window.draw(rectangle);
                        }
                    window.display();
                    break;
                }
            }
                // we don't process other types of events
            default:
                break;
            }
        }
        if (rightClickOn)
        {
            // clear the window with black color
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
            window.display();
            board.applyRulesOnce();
            //break;
        }
    }
    return 0;
}