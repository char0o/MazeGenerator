#include "Maze.h"
#define MAZE_SIZE 16
Maze::Maze() : visited()
{
	this->map = new TileMap(MAZE_SIZE, MAZE_SIZE);
	std::random_device rd;
	this->rng = std::default_random_engine{rd()};
	generateEndTile();
}
Maze::Maze(int sizeX, int sizeY) : visited()
{
	this->map = new TileMap(sizeX, sizeY);
	std::random_device rd;
	this->rng = std::default_random_engine{rd()};
	generateEndTile();
}
Maze::~Maze()
{
	delete this->map;
}
TileMap* Maze::getMap()
{
	return this->map;
}
Tile& Maze::getEndTile()
{
	return *this->endTile;
}
void Maze::setEndTile(Tile& tile)
{
	this->endTile = &tile;
}
void Maze::generateEndTile()
{
	sf::Vector2f position = Vector2f(0,0);
	int rdmPos = rand() % MAZE_SIZE;
	Direction dir = static_cast<Direction>(rand() % 4);
	switch (dir)
	{
	case Direction::Up:
		position = sf::Vector2f(rdmPos, 0);
		this->getMap()->at(rdmPos, 0).removeWall(Direction::Up);
		break;

	case Direction::Down:
		position = sf::Vector2f(rdmPos, (MAZE_SIZE - 1));
		this->getMap()->at(rdmPos, MAZE_SIZE - 1).removeWall(Direction::Down);
		break;
	case Direction::Left:
		position = sf::Vector2f(0, rdmPos);
		this->getMap()->at(0, rdmPos).removeWall(Direction::Left);
		break;
	case Direction::Right:
		position = sf::Vector2f((MAZE_SIZE - 1), rdmPos);
		this->getMap()->at(MAZE_SIZE - 1, rdmPos).removeWall(Direction::Right);
		break;
	}
	this->endTile = &this->getMap()->at(position.x, position.y);
}
void Maze::backTracker(Tile& current, std::set<Tile*>& visited, RenderWindow& window)
{
	window.clear();
	this->getMap()->drawTiles(window);
	window.display();
	visited.insert(&current);
	std::vector<Tile*> neighbors = map->getNeighbors(current);
	std::shuffle(std::begin(neighbors), std::end(neighbors), this->rng);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (visited.find(neighbors[i]) == visited.end())
		{
			map->removeWallsBetween(current, *neighbors[i]);
			backTracker(*neighbors[i], visited, window);

		}
	}
}
void Maze::bfs(Tile& start, RenderWindow& window)
{
	std::vector<Tile*> visited;
	std::queue<Tile*> frontier;
	std::unordered_map<Tile*, Tile*> parent;
	parent[&start] = NULL;
	frontier.push(&start);
	visited.push_back(&start);
	while (!frontier.empty())
	{
		Tile* tile = frontier.front();
		tile->setColor(Color(255, 0, 0, 255));
		frontier.pop();
		std::vector<Tile*> neighbors = this->getMap()->getNeighborsWalls(*tile);
		for (int i = 0; i < neighbors.size(); i++)
		{
			neighbors[i]->setColor(Color(255, 0, 0, 255));			
			window.clear();
			this->getMap()->drawTiles(window);
			window.display();
			if (neighbors[i] == this->endTile)
			{
				parent[neighbors[i]] = tile;
				std::vector<Tile*> path;
				for (Tile* current = neighbors[i]; current != NULL; current = parent[current])
				{
					path.push_back(current);
				}
				std::reverse(path.begin(), path.end());
				this->getMap()->resetColor();
				for (int j = 0; j < path.size(); j++)
				{
					path[j]->setColor(Color(125, 125, 0, 255));
					window.clear();
					this->getMap()->drawTiles(window);
					window.display();
				}
				return;
			}
			if (std::find(visited.begin(), visited.end(), neighbors[i]) == visited.end())
			{
				parent[neighbors[i]] = tile;
				frontier.push(neighbors[i]);
				visited.push_back(neighbors[i]);
			}
		}
	}
}