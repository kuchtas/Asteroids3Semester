#ifndef _ROCKETSHIP_HPP_			//Class repsonsible for all the logic behind Rocketship movement, it's status and such
#define _ROCKETSHIP_HPP_

#include "SFML/Graphics.hpp"
#include "Definitions.hpp"

class Rocketship : public sf::Drawable, public sf::Transformable
{

public:
	Rocketship();
	~Rocketship();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleArrowKeyMovement(sf::Keyboard::Key key);
	void update();
	void hit();
	bool isAlive();
	void ressurect();
	int getLifes();
	float x = Width / 2, y = Height / 2;
	float angle = 270;
	int sincehit = 0;
	
private:
	int life = 3;
	bool thrust;
	float dx = 0, dy = 0;
	int MaxSpeed = 15;
	float speed=0;
	sf::ConvexShape shape;
};
#endif
