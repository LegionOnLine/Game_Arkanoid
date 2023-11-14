#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Ball.h"
#include "Paddle.h"


class Game{
private:
	sf::RenderWindow* window;
	std::vector<Ball*> balls;
	Paddle* paddle;

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

