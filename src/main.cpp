#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "TileMap.h"
#include "Maze.h"


int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    auto window = sf::RenderWindow{ { 800u, 600u }, "Maze generator" };
    window.setFramerateLimit(60);
    Maze* maze = new Maze(16, 16);
    std::set<Tile*> visited;
    maze->backTracker(maze->getEndTile(), visited);
    maze->bfs(maze->getMap()->at(4, 4), window);
    while(window.isOpen())
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
