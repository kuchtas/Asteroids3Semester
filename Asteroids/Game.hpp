#ifndef _GAME_HPP_			//Class responsible for putting everything together
#define _GAME_HPP_
#include "SFML/Graphics.hpp"
#include "Rocketship.hpp"
#include "Rocks.hpp"
#include "Entity.hpp"
#include "Definitions.hpp"
#include "Bullet.hpp"
class Game
{
public:
	Game();
	~Game();
	void run();

	int score = 0;
	int sinceshot=0;
	int counter = 0;
	bool wait = false;
	void setUI(sf::Text&, sf::Text&, sf::Font&, int, int);
	void GameOver(sf::Font, sf::Text, sf::Text, int);

private:
	Rocketship Rocket;
	std::vector<Rocks> asteroids; //vector of asteroids
	std::vector<Bullet> bullets; //vector of bullets
	sf::Font Arial;
	sf::Text ScoreText;
	sf::Text LifeText;
	sf::Text GameOverText;

	void processEvents();
	void update();
	void render();

	sf::RenderWindow window;
};
#endif