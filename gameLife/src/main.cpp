#include "board.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
constexpr unsigned short WINDOW_WIDTH = 800;
constexpr unsigned short WINDOW_HEIGHT = 800;
constexpr float CELL_WIDTH = static_cast<float>(WINDOW_WIDTH) / BOARD_WIDTH;
constexpr float CELL_HEIGHT = static_cast<float>(WINDOW_HEIGHT) / BOARD_HEIGHT;
int main()
{
	board board;
	board.printBoardArray();
    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game of Life");
    window.setVerticalSyncEnabled(true); // call it once, after creating the window

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        sf::RectangleShape rectangle(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
        window.draw(rectangle);
        

        // end the current frame
        window.display();
    }

    return 0;
}