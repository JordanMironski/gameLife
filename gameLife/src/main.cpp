#include "board.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
constexpr unsigned short WINDOW_WIDTH = 800;
constexpr unsigned short WINDOW_HEIGHT = 800;
constexpr float CELL_WIDTH = static_cast<float>(WINDOW_WIDTH) / BOARD_WIDTH;
constexpr float CELL_HEIGHT = static_cast<float>(WINDOW_HEIGHT) / BOARD_HEIGHT;
int main()
{
    /*board board({{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };*/
    bool rightClickOn = false; // flag indicating weather to accept mouse inputs (left clicks)
    std::array<std::array<cell, BOARD_WIDTH>, BOARD_HEIGHT> init;
    cell a;
    cell d;
    a.setAlive();
    d.setDead();
    //init[0] = { d,d,a };
    //init[1] = { a,d,a };
    //init[2] = { d,a,a };
    
    board board(init);
    bool flag = true;
    /*board.arr[0] = { a,a,d };
    board.arr[1] = { a,a,d };
    board.arr[2] = { d,d,d };
	*/
    //board.printBoardArray();
    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game of Life");
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
            /*// "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();*/
        }
        /*if (rightClickOn)
            continue;
        else if (flag)
        {
            board = init;
            flag = false;
        }*/
        
        // clear the window with black color
        window.clear(sf::Color::Black);
        for (auto i = 0; i < BOARD_HEIGHT; ++i)
            for (auto j = 0; j < BOARD_WIDTH; ++j)
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