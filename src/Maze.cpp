#include "Maze.h"
Maze::Maze() : visited()
{
	this->map = new TileMap(16, 16);
	this->rng = std::default_random_engine{};
}
Maze::Maze(int sizeX, int sizeY) : visited()
{
	this->map = new TileMap(sizeX, sizeY);
	this->rng = std::default_random_engine{};
}
Maze::~Maze()
{
	delete this->map;
}
TileMap* Maze::getMap()
{
	return this->map;
}
void Maze::backTracker(Tile& current, std::set<Tile*>& visited)
{
	visited.insert(&current);
	std::vector<Tile*> neighbors = map->getNeighbors(current);
	std::shuffle(std::begin(neighbors), std::end(neighbors), this->rng);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (visited.find(neighbors[i]) == visited.end())
		{
			map->removeWallsBetween(current, *neighbors[i]);
			backTracker(*neighbors[i], visited);
		}
	}
}