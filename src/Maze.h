#pragma once
#include <set>
#include <queue>
#include "TileMap.h"
#include <unordered_map>
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
	void backTracker(Tile& current, std::set<Tile*>& visited, RenderWindow& window);
	void generateEndTile();
	void bfs(Tile& start, RenderWindow& window);
private:
	TileMap* map;
	Tile* endTile;
	std::set<Tile*> visited;
	std::default_random_engine rng;
};