#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Direction.h"

using namespace sf;
class Tile
{
public:
	Tile();
	Tile(float posX, float posY);
	~Tile();
	Vector2f getPosition();
	void setPosition(const Vector2f& position);
	void setColor(const Color& color);
	void draw(RenderWindow& window);
	void createWalls();
	void removeWall(Direction direction);
	bool hasWall(Direction direction);
	bool operator==(const Tile& other) const;
private:
	const int size = 32;
	Vector2f position;
	std::map<Direction, std::unique_ptr<RectangleShape>> walls;
	std::unique_ptr<RectangleShape> shape;
};
