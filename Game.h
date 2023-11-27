#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"

class Game {
private:

	sf::Font font;
	sf::Text textPoints;
	sf::Text textLives;
	sf::Text textGame;

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
	int blockCount;

	int playerPoints{ 0 };
	int playerLives{ 2 };

	int blockDist{ 10 };
	float blockWidth; // { static_cast<float>(((windowWidth - 100 - (blocksCols * blockDist)) / blocksCols)) };
	float blockHight; // { blockWidth * 0.3f };

	bool gameOver{ false };

public:
	Game();
	~Game();

	bool GameWorking();

	//Basic Functionality
	void initGUI();
	void startNewGame();

	void initBlocks();
	void initWindow();
	void initMainFrame();


	void pollEvent();
	void update();
	void updateGui();
	void updateGameText();


	void renderGui();
	void draw();
};

