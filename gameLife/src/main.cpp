#include "game.hpp"
#include "settings.hpp"
int main()
{
    Settings settings;

    // create the window
    sf::RenderWindow window(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "Game of Life");
    window.setVerticalSyncEnabled(true); // call it once, after creating the window
    window.clear(sf::Color::Black);
    window.display();
    auto factory = StateFactory{ [] (sf::RenderWindow& window, Settings& settings) { return doMainMenu(window, settings); } };

    while (factory.m_function)
        factory = factory.m_function(window, settings);

    return 0;
}