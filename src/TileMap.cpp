#include "TileMap.h"
#include "Tile.h"
TileMap::TileMap()
{
	this->sizeX = 0;
	this->sizeY = 0;
	this->tiles = NULL;
}
TileMap::TileMap(int sizeX, int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->tiles = new Tile * [sizeX];
	for (int i = 0; i < sizeX; i++)
	{
		tiles[i] = new Tile[sizeY];
	}
	this->init();
}
TileMap::~TileMap()
{
	for (int i = 0; i < this->sizeX; i++)
	{
		delete[] this->tiles[i];
	}
	delete[] this->tiles;
}
void TileMap::init()
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			tiles[i][j].setPosition(sf::Vector2f(i, j));
			tiles[i][j].createWalls();
		}
	}
}
Tile& TileMap::at(int x, int y)
{
	if (x < 0 || x > this->sizeX - 1 || y < 0 || y > this->sizeY - 1)
	{
		throw std::out_of_range("Tilemap out of range");
	}
	return this->tiles[x][y];
}
int TileMap::getSizeX()
{
	return this->sizeX;
}
int TileMap::getSizeY()
{
	return this->sizeY;
}
void TileMap::drawTiles(sf::RenderWindow& window)
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			tiles[i][j].draw(window);
		}
	}
}
std::vector<Tile*> TileMap::getNeighbors(Tile& tile)
{
	std::vector<Tile*> vec;
	sf::Vector2i directions[4] = {
		Vector2i(1, 0),
		Vector2i(0, 1),
		Vector2i(-1, 0),
		Vector2i(0, -1)
	};
	int newX = 0;
	int newY = 0;
	for (int i = 0; i < 4; i++)
	{
		newX = tile.getPosition().x + directions[i].x;
		newY = tile.getPosition().y + directions[i].y;
		if (newX >= 0 && newX < this->sizeX && newY >= 0 && newY < this->sizeY)
		{
			vec.push_back(&tiles[newX][newY]);
		}
	}
	return vec;
}
std::vector<Tile*> TileMap::getNeighborsWalls(Tile& tile)
{
	std::vector<Tile*> vec;
	sf::Vector2f directions[4] = {
		Vector2f(0, -1),
		Vector2f(1, 0),
		Vector2f(0, 1),
		Vector2f(-1, 0)
	};
	Vector2f newPos;
	for (int i = 0; i < 4; i++)
	{
		Direction dir = static_cast<Direction>(i);
		newPos = tile.getPosition() + directions[i];
		switch (dir)
		{
		case Direction::Up:
			if (!tile.hasWall(Direction::Up))
			{
				vec.push_back(&tiles[int(newPos.x)][int(newPos.y)]);
			}
			break;
		case Direction::Down:
			if (!tile.hasWall(Direction::Down))
			{
				vec.push_back(&tiles[int(newPos.x)][int(newPos.y)]);
			}
			break;
		case Direction::Left:
			if (!tile.hasWall(Direction::Left))
			{
				vec.push_back(&tiles[int(newPos.x)][int(newPos.y)]);
			}
			break;
		case Direction::Right:
			if (!tile.hasWall(Direction::Right))
			{
				vec.push_back(&tiles[int(newPos.x)][int(newPos.y)]);
			}
			break;

		}

	}
	return vec;
}
void TileMap::resetColor()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			this->at(i, j).setColor(Color(255, 255, 255, 255));
		}
	}
}
void TileMap::removeWallsBetween(Tile& start, Tile& end)
{
	sf::Vector2f directionVector = end.getPosition() - start.getPosition();
	Direction startDirection = Direction::Up;
	Direction endDirection = Direction::Up;
	if (directionVector.x != 0)
	{
		directionVector.x = (directionVector.x > 0) ? 1 : -1;
		startDirection = (directionVector.x == -1) ? Direction::Left : Direction::Right;
		endDirection = (directionVector.x == -1) ? Direction::Right : Direction::Left;
	}
	if (directionVector.y != 0)
	{
		directionVector.y = (directionVector.y > 0) ? 1 : -1;
		startDirection = (directionVector.y == -1) ? Direction::Up : Direction::Down;
		endDirection = (directionVector.y == -1) ? Direction::Down : Direction::Up;
	}
	start.removeWall(startDirection);
	end.removeWall(endDirection);
}