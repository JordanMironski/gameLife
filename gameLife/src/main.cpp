#include "board.hpp"
#include "settings.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
//extern constexpr unsigned short WINDOW_WIDTH = 800;
//extern constexpr unsigned short WINDOW_HEIGHT = 800;
float CELL_WIDTH = static_cast<float>(settings.WINDOW_WIDTH) / settings.BOARD_WIDTH;
float CELL_HEIGHT = static_cast<float>(settings.WINDOW_HEIGHT) / settings.BOARD_HEIGHT;
int main()
{
   
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
    for (const auto& row : init)
    {
        for (const auto& el : row)
            std::cout << el.getValue() << " ";
        std::cout << std::endl;
    }
    bool flag = true;
    /*board.arr[0] = { a,a,d };
    board.arr[1] = { a,a,d };
    board.arr[2] = { d,d,d };
	*/
    //board.printBoardArray();
    // create the window
    sf::RenderWindow window(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "Game of Life");
    window.setVerticalSyncEnabled(true); // call it once, after creating the window
    //window.setFramerateLimit(8);
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

                    auto j = floor(event.mouseButton.x / CELL_WIDTH);
                    auto i = floor(event.mouseButton.y / CELL_HEIGHT);
                    std::cout << i << " " << j << std::endl;
                    init[i][j] = a;
                }
            }
                // we don't process other types of events
            default:
                break;
            }
        }        
        // clear the window with black color
        window.clear(sf::Color::Black);
        for (auto i = 0; i < settings.BOARD_HEIGHT; ++i)
            for (auto j = 0; j < settings.BOARD_WIDTH; ++j)
            {
                sf::RectangleShape rectangle(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
                rectangle.setPosition((CELL_WIDTH) * static_cast<float>(j), CELL_HEIGHT * static_cast<float>(i));

                if (!board.getCellValue(i,j)) // if is alive set color black (0, 0, 0)
            		rectangle.setFillColor(sf::Color(0, 0, 0)); //else it's white by default
                window.draw(rectangle);
            }
    	
        // end the current frame
        window.display();
        board.applyRulesOnce();
        //puts("------------------------------------------");
        //board.printBoardArray();
        
        //break;
    }
    return 0;
}