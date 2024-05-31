#pragma once
#include "Tile.h"
#include "SFML/Graphics.hpp"
#include <memory>
#define MAP_SIZE 16
class TileMap
{
public:
	TileMap();
	TileMap(int sizeX, int sizeY);
	~TileMap();
	int getSizeX();
	int getSizeY();
	Tile& at(int x, int y);
	void init();
	void drawTiles(sf::RenderWindow& window);
	void removeWallsBetween(Tile& start, Tile& end);
	std::vector<Tile*> getNeighbors(Tile& tile);
	std::vector<Tile*> getNeighborsWalls(Tile& tile);
	void resetColor();
private:
	Tile** tiles;
	int sizeX;
	int sizeY;
};
