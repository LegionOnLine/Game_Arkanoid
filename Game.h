#pragma once
#include <SFML/Graphics.hpp>

#include "Ball.h"

class Game{
private:
	sf::RenderWindow* window;
	std::vector<Ball*> balls;
	Ball ball;

public:
	Game();
	~Game() = default;

	void update();
	void draw();
	bool GameWorking();
	void initWindow();
};

