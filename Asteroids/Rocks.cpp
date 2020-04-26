#include "Rocks.hpp"


Rocks::Rocks()
{
	dx = rand() % 8 - 4;
	dy = rand() % 8 - 4;
	name = "asteroid";

	shape.setPointCount(8);

	//ASTEROIDS <10,radius> // the asteroid is a shape consisting of 8 points distributed around the circle like an octagon
							// we achieve this more realistically looking rock by randomizing the distance of the point from the circle center
	shape.setPoint(0, sf::Vector2f((10 + (rand() % (radius - 10 + 1))), 0.0f)); // 0 -
	shape.setPoint(1, sf::Vector2f((10 + (rand() % (radius - 10 + 1)))*sqrt(2)/2, (10 + (rand() % (radius - 10 + 1)))*sqrt(2)/2)); //+ -

	shape.setPoint(2, sf::Vector2f(0.0f, (10 + (rand() % (radius - 10 + 1)))));// + 0
	shape.setPoint(3, sf::Vector2f(-(10 + (rand() % (radius - 10 + 1)))*sqrt(2)/2, 10.0*sqrt(2)/2)); // + +

	shape.setPoint(4, sf::Vector2f(-(10 + (rand() % (radius - 10 + 1))), 0.0f));// 0 +
	shape.setPoint(5, sf::Vector2f(-(10 + (rand() % (radius - 10 + 1)))*sqrt(2)/2, -(10 + (rand() % (radius - 10 + 1)))*sqrt(2)/2)); //- +

	shape.setPoint(6, sf::Vector2f(0.0f, -(10 + (rand() % (radius - 10 + 1)))));// - 0
	shape.setPoint(7, sf::Vector2f((10 + (rand() % (radius - 10 + 1)))*sqrt(2)/2, -(10 + (rand() % (radius - 10 + 1)))*sqrt(2)/2)); //- -

	shape.setFillColor(sf::Color::Black);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(3);
}

Rocks::~Rocks()
{
}

void Rocks::update()
{
	if (dx == 0 || dy == 0) //sometimes the asteroids spawn in the top of the window and go to the right or to the left :/ 
	{						// this if statement is supposed to move them from this spot
		dx = rand() % 8 - 4;
		dy = rand() % 8 - 4;
	}
	x += dx;
	y += dy;

	if (x > Width) x = 0; if (x < 0) x = Width;		// if the asteroid goes outside of the game window, 
	if (y > Height) y = 0; if (y < 0) y = Height;	//it comes back on the other side of the screen like in Pac-Man
}

void Rocks::kill() //changing the status of asteroid
{
	alive = false;
}