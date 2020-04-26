#include "Entity.hpp"

Entity::Entity()
{
	alive = true;
}


Entity::~Entity()
{
}

void Entity::setup(int X, int Y, float Angle, int Radius )
{
	x = X; y = Y; angle = Angle; R = Radius;
}

void Entity::update() //this function is virtual 
{
}

void Entity::draw(sf::RenderWindow &target) 
{
	shape.setPosition(x, y);
	shape.setRotation(angle + 90);
	target.draw(shape);
}