#pragma once
#include <SFML/Graphics.hpp>

#include "Ball.h"

class Game{
private:
	sf::RenderWindow* window;
	std::vector<Ball*> balls;


public:
	Game();
	~Game();

	//Basic Functionality
	void pollEvent();
	void update();
	void draw();


	bool GameWorking();
	void initWindow();

};

