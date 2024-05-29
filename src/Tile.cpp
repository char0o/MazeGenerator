#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Tile.h"
using namespace sf;
Tile::Tile()
{
	this->shape = std::make_unique<RectangleShape>(Vector2f(this->size, this->size));
	this->setType(TileType::Wall);
}
Tile::Tile(float posX, float posY)
{
	this->shape = std::make_unique<RectangleShape>(Vector2f(this->size, this->size));
	this->shape->setPosition(Vector2f(posX, posY));
}
Tile::~Tile()
{

}
void Tile::createWalls()
{
	Color wallcolor(100, 50, 100, 255);
	for (int i = Direction::Up; i <= Direction::Left; i++)
	{
		switch (static_cast<Direction>(i))
		{
		case Direction::Up:
			if (position.y >= 0)
			{
				std::unique_ptr<RectangleShape> rect = std::make_unique<RectangleShape>();
				rect->setPosition(Vector2f(position.x * 32, position.y * 32));
				rect->setSize(Vector2f(32, 2));
				rect->setFillColor(wallcolor);
				walls.emplace(Direction::Up, std::move(rect));
			}
			break;
		case Direction::Right:
			if (position.x < 16)
			{
				std::unique_ptr<RectangleShape> rect = std::make_unique<RectangleShape>();
				rect->setPosition(Vector2f(position.x * 32 + 30, position.y * 32));
				rect->setFillColor(wallcolor);
				rect->setSize(Vector2f(2, 32));
				walls.emplace(Direction::Right, std::move(rect));
			}
			break;
		case Direction::Down:
			if (position.y < 16)
			{
				std::unique_ptr<RectangleShape> rect = std::make_unique<RectangleShape>();
				rect->setPosition(Vector2f(position.x * 32, (position.y * 32) + 30));
				rect->setSize(Vector2f(32, 2));
				rect->setFillColor(wallcolor);
				walls.emplace(Direction::Down, std::move(rect));
			}
			break;
		case Direction::Left:
			if (position.x >= 0)
			{
				std::unique_ptr<RectangleShape> rect = std::make_unique<RectangleShape>();
				rect->setPosition(Vector2f(position.x * 32, position.y * 32));
				rect->setSize(Vector2f(2, 32));
				rect->setFillColor(wallcolor);
				walls.emplace(Direction::Left, std::move(rect));
			}
			break;
		}
	}
}
void Tile::setType(TileType type)
{
	this->type = type;
	switch (type)
	{
	case TileType::Empty:
		this->setColor(sf::Color(50, 50, 50, 255));
		break;
	case TileType::Wall:
		this->setColor(sf::Color(200, 200, 200, 255));
		break;
	}
}
TileType Tile::getType()
{
	return this->type;
}
Vector2f Tile::getPosition()
{
	return this->position;
}
void Tile::setPosition(const Vector2f& position)
{
	this->position = position;
	this->shape->setPosition(Vector2f(position.x * size, position.y * size));
}
void Tile::removeWall(Direction direction)
{
	if (this->walls[direction] != NULL)
	{
		this->walls[direction] = NULL;
	}
}
void Tile::draw(RenderWindow& window)
{

	window.draw(*this->shape);
	for (int i = Direction::Up; i <= Direction::Left; i++)
	{
		Direction dir = static_cast<Direction>(i);
		if (walls[dir] != NULL)
		{
			window.draw(*walls[dir]);
		}
	}
}
void Tile::setColor(const Color& color)
{
	this->shape->setFillColor(color);
}
