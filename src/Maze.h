#pragma once
#include <set>
#include "TileMap.h"
#include <random>
#include <algorithm>
#include <cstdlib>
class Maze {
public:
	Maze();
	Maze(int sizeX, int sizeY);
	~Maze();
	TileMap* getMap();
	void setEndTile(Tile& endTile);
	Tile& getEndTile();
	void backTracker(Tile& current, std::set<Tile*>& visited);
	void generateEndTile();
private:
	TileMap* map;
	Tile* endTile;
	std::set<Tile*> visited;
	std::default_random_engine rng;
};