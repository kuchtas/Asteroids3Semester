#include "Bullet.hpp"

Bullet::Bullet()
{
	name = "bullet"; // the bullet looks like a small yellow triangle 
	shape.setPointCount(4);
	shape.setPoint(0, sf::Vector2f(0.0f,-1.0f)); 
	shape.setPoint(1, sf::Vector2f(1.0f, 1.0f));
	shape.setPoint(2, sf::Vector2f(0.0f, 1.0f));
	shape.setPoint(3, sf::Vector2f(-1.0f, 1.0f));

	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOutlineColor(sf::Color::Yellow);
	shape.setOutlineThickness(3);
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	dx = cos(angle*DEGTORAD)*6 ;
	dy = sin(angle*DEGTORAD)*6 ;
	x += dx;
	y += dy;
	if (x > Width || x<0 || y>Height || y < 0) // we elliminate all of the bullets that go off the screen
		kill();
}

void Bullet::kill() 
{
	alive = false;
}
