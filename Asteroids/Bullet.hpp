#ifndef _BULLET_HPP_			//Class responsible for updating bullets
#define __BULLET_HPP_
#include "Entity.hpp"
#include "Definitions.hpp"
class Bullet :public Entity
{
public:
	Bullet();
	~Bullet();
	void update(); 
	void kill();
};
#endif