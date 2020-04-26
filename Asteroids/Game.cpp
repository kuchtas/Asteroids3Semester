#include "Game.hpp"

Game::Game() : window(sf::VideoMode(Width, Height), "Asteroids!")
{
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(true);

	try
	{
		Arial.loadFromFile("arial.ttf");
	}
	catch(sf::Font Arial)
	{ 
	}
}

Game::~Game()
{
	window.close();
}

void Game::setUI(sf::Text& Score, sf::Text& Life, sf::Font& Arial, int score, int lifes) // setting up things such as the font, 
{																						//it's size and colour and the text to display
	Score.setFont(Arial);
	Life.setFont(Arial);

	Score.setCharacterSize(30);
	Life.setCharacterSize(30);

	Score.setPosition(0, 0);
	Life.setPosition(0, Height / 20);

	Score.setFillColor(sf::Color::White);
	Life.setFillColor(sf::Color::Red);

	Score.setString(std::to_string(score));
	Life.setString(std::to_string(lifes));
}

void Game::GameOver(sf::Font Arial, sf::Text Score, sf::Text GameOver,int score) //GAME OVER SCREEN
{
	window.clear(sf::Color::Black);
	Score.setFont(Arial);
	Score.setCharacterSize(30);
	Score.setString(std::to_string(score));
	GameOver.setFont(Arial);
	GameOver.setString("\t\t\t\t\tYour score is: ");
	GameOver.setCharacterSize(30);
	GameOver.setPosition(Width / 5, Height / 2);
	window.draw(GameOver);
	GameOver.setString("\nPress Escape to quit or press Enter to continue");
	Score.setPosition(Width / 1.8, Height / 2);
	window.draw(Score);
	window.draw(GameOver);
	window.display();
}

void Game::run() //main game loop 
{
	while (window.isOpen())
	{
		if(!wait) processEvents(); // this function takes care of all of the inputs 

		if (Rocket.isAlive()&&!wait)
			update();
		else
		{		
			GameOver(Arial,ScoreText,GameOverText,score); //GAME OVER SCREEN
			bullets.clear();
			asteroids.clear();
			wait = true;
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					if (event.key.code == sf::Keyboard::Enter)
					{
						wait = false;
						score = 0;
						Rocket.ressurect();
						window.clear();
					}	
					break;
				}
			}
		}
		if(!wait) render(); // this function takes care of displaying everything in the game window
		if(counter%60==0&&!wait) score=score+10;
		counter++; //this counter helps to tell how many frames have elapsed, it is used to get points every second, since the program works in 60 fps
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) // we can close the game by clicking on the X or by pressing Escape
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			break;
		}
	}

	Rocket.handleArrowKeyMovement(event.key.code); // Rocketship movement

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&sinceshot>=20) //SHOOTING
	{
		Bullet b;
		b.setup(Rocket.x, Rocket.y, Rocket.angle, 10); // spawning the bullets in the direction of the Rocketship
		bullets.push_back(b);
		sinceshot = 0;
	}
}

void Game::update()
{
	Rocket.update(); //updating the movement of the Rocketship (without collisions)

	//Bullets and Asteroids updating and collisions etc.
	std::vector<Bullet>::iterator start_bullets = bullets.begin(); //creating an iterator at the beginning which lets me work with the bullet vector
	while (start_bullets != bullets.end()) //going through the whole vector
	{
		if (start_bullets->alive) //updating all of the alive bullets
		{
			start_bullets->update();
			++start_bullets;
		}
		else
			start_bullets = bullets.erase(start_bullets); //erasing all of the dead bullets
	}

	if (asteroids.size() < 10) // here we specify the maximum number of asteroids on screen 
	{
		Rocks r;
		if (asteroids.size() % 2 == 0) // this way the asteroids dont spawn all in the same place, it looks more random
			r.setup(rand() % Width + Width, rand() % Height, rand() % 360, 10); // all of the spawning takes place on the brink of the screen 
		else
			r.setup(rand() % Width, rand() % Height + Height, rand() % 360, 10);

		asteroids.push_back(r); //adding new asteroids to the vector
	}

	std::vector<Rocks>::iterator start_asteroids = asteroids.begin(); //creating an iterator at the beginning which lets me work with the asteroid vector
	while (start_asteroids != asteroids.end()) //going through the whole vector
	{
		//UPDATING ALIVE ASTEROIDS AND ERASING DEAD ONES
		if (start_asteroids->alive) //updating all of the alive asteroids
		{
			start_asteroids->update();
			++start_asteroids;
		}
		else
		{
			score = score + 100;
			start_asteroids = asteroids.erase(start_asteroids); //erasing all of the dead asteroids
		}		
	}

	start_asteroids = asteroids.begin(); //setting the iterator back on the first asteroid

	while (start_asteroids != asteroids.end())  //going through the whole vector
	{
		//ASTEROID  - BULLET COLLISIONS
		start_bullets = bullets.begin(); //setting the iterator back on the first bullet
		while (start_bullets != bullets.end()) //going through the whole vector
		{
			if (!start_bullets->alive) 
			{
				++start_bullets;
				continue;
			}

			if (((start_asteroids->x - start_bullets->x)*(start_asteroids->x - start_bullets->x) //Bullet - asteroid collision 
				+ (start_asteroids->y - start_bullets->y)*(start_asteroids->y - start_bullets->y)) <= 300) ///TODO the hitbox might need some adjusting
			{
				start_bullets->kill(); // changing the alive status of the bullet
				start_asteroids->kill();// changing the alive status of the asteroid
				break;
			}
			++start_bullets;
		}

		//ASTEROID - ROCKET COLLISIONS
		if ((((Rocket.x - start_asteroids->x)*(Rocket.x - start_asteroids->x) +
			(Rocket.y - start_asteroids->y)*(Rocket.y - start_asteroids->y)) <= 1600) && Rocket.sincehit>100)///This hitbox may need some adjusting
		{
			Rocket.hit();
			Rocket.sincehit = 0;
		}
		++start_asteroids;
	}
	sinceshot++;
}
	

void Game::render()
{
	window.clear(sf::Color::Black);

	window.draw(Rocket); //drawing Rocketship

	//DISPLAYING THE ASTEROIDS AND BULLETS
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) // displaying all of the bullets on screen
		it->draw(window);
	for (std::vector<Rocks>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)// displaying all of the asteroids on screen
		it->draw(window);

	setUI(ScoreText, LifeText, Arial, score, Rocket.getLifes()); // setting up things such as the font, it's size and colour and the text to display

	window.draw(ScoreText);
	window.draw(LifeText);

	window.display();
}


