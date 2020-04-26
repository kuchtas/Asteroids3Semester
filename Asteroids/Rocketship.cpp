#include "Rocketship.hpp"
Rocketship::Rocketship()
{ 
	life = 3;
	shape.setPointCount(3); // the rocketship as an elongated triangle
	shape.setPoint(0, sf::Vector2f(0.0f, -20.0f));
	shape.setPoint(1, sf::Vector2f(7.5f, 7.5f));
	shape.setPoint(2, sf::Vector2f(-7.5f, 7.5f));

	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(2);
	shape.setPosition(Width/2, Height/2); 
	shape.setOrigin(Width / 2, Height/2);
}

void Rocketship::draw(sf::RenderTarget& target, sf::RenderStates states) const // the drawing of the ship
{
	states.transform *= getTransform(); 
	target.draw(shape, states);
}

Rocketship::~Rocketship()
{
}

void Rocketship::handleArrowKeyMovement(sf::Keyboard::Key key)  // this function handles the movement of the ship
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) angle += 3; // the change in the angle may need some adjusting 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) angle -= 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) thrust = true; // thrust makes the ship accelerate
	else thrust = false; // if up arrow key is not pressed, the rocketship slows down
}

void Rocketship::update() // rocketship physics
{
	sincehit++; // this variable counts time since the ship got hit by an asteroid
	if (sincehit>=100)
	{
		shape.setOutlineColor(sf::Color::Green);
	}
	if (thrust) //if we accelerate we make the dx and dy greater, which leads to greater displacement 
	{
		dx += cos(angle*DEGTORAD)*0.2;
		dy += sin(angle*DEGTORAD)*0.2;
	}
	else // if we dont accelerate we slow down
	{
		dx *= 0.99;
		dy *= 0.99;
	}
	speed = sqrt(dx*dx + dy * dy); 
	if (speed > MaxSpeed) // I thought the rocketship should have some constraints on it's maximum speed, this function doesn't let it be too fast
	{
		dx *= MaxSpeed / speed;
		dy *= MaxSpeed / speed;
	}

	x += dx; //changing the position
	y += dy;

	if (x > Width) x = 0; if (x < 0) x = Width; //if the rocketship goes out of the game bounds, 
	if (y > Height) y = 0; if (y < 0) y = Height; //it comes back on the other side of the window like in Pac-Man

	setPosition(x, y);
	setRotation(angle + 90);
}
void Rocketship::hit()
{
	life--;
	shape.setOutlineColor(sf::Color::Red);
}

bool Rocketship::isAlive()
{
	if (life <= 0)
		return false;
	else 
		 return true;
}
void Rocketship::ressurect()
{
	life = 3;
	shape.setOutlineColor(sf::Color::Green);
	x = Width / 2;
	y = Height / 2;
	dx = dy = 0;
}

int Rocketship::getLifes()
{
	return life;
}