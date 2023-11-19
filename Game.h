#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"

class Game {
private:
	//sf::VertexArray lines(sf::LineStrip, 2);

	

	int windowWidth{ 1000 }, windowHeight{ 600 };
	sf::RenderWindow* window;
	std::vector<Ball*> balls;
	Paddle* paddle;
	std::vector<std::vector<Block*>> blocks;
	//Block* block;

	int blocksCols{ 10 };
	int blocksRows{ 3 };

	int blockDist{ 10 };
	float blockWidth{ static_cast<float>(((windowWidth - 100 - (blocksCols * blockDist)) / blocksCols)) };
	float blockHight{ blockWidth * 0.3f };

public:
	Game();
	~Game();

	//Basic Functionality
	void pollEvent();
	void update();
	void draw();


	bool GameWorking();
	void initBlocks();
	void initWindow();

};

