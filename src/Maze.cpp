#include "Maze.h"
Maze::Maze() : visited()
{
	this->map = new TileMap(16, 16);

}
Maze::Maze(int sizeX, int sizeY) : visited()
{
	this->map = new TileMap(sizeX, sizeY);
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
	visited.insert(&this->map->at(current.getPosition().x, current.getPosition().y));
	std::vector<Tile*> neighbors = map->getNeighbors(current);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (visited.find(neighbors[i]) != visited.end())
		{

		}
	}
}