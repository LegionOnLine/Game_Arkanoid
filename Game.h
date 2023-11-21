#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"

class Game {
private:

	//Frame:
	sf::VertexArray* mainFrame;
	sf::Vector3f mainFrameCoords;
	float mainFrameWidth;
	float mainFrameBottom;
	sf::Color frameColor;
	

	int windowWidth{ 1800 }, windowHeight{ 1200 };
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


	bool GameWorking();
	void initBlocks();
	void initWindow();
	void initMainFrame();

	void pollEvent();
	void update();
	void draw();
};

