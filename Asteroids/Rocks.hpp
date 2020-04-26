#ifndef _ROCKS_HPP			//Class responsible for updating asteroids
#define _ROCKS_HPP
#include "Entity.hpp"
#include "Definitions.hpp"
class Rocks:public Entity 
{
	int radius = 20;
public:
	Rocks();
	~Rocks();

	void update();
	void kill();
};
#endif
