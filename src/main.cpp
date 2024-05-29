#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "TileMap.h"
#include "Maze.h"


int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Maze generator" };
    window.setFramerateLimit(144);
    Maze* maze = new Maze(16, 16);
    maze->getMap()->removeWallsBetween(maze->getMap()->at(2, 2), maze->getMap()->at(3, 2));
    while (window.isOpen())
    {
        for (sf::Event event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        maze->getMap()->drawTiles(window);
        window.display();
    }
}
