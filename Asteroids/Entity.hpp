#ifndef _ENTITY_HPP_		// this class is the base for asteroids and bullets
#define _ENTITY_HPP_
#include <string>
#include <SFML\Graphics.hpp>

class Entity 
{
public:
	float x, y, dx, dy, R, angle;
	bool alive; 
	std::string name;

	Entity();
	~Entity();

	void setup(int X, int Y, float Angle = 0, int Radius = 1);
	virtual void update();
	void draw(sf::RenderWindow &target);

	sf::ConvexShape shape;
};

#endif