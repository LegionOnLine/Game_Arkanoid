#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"

class Game {
private:

	//Text Objects
	sf::Font font;
	sf::Text textPoints;
	sf::Text textLives;
	sf::Text textGame;

	//Frame:
	sf::VertexArray* mainFrame;
	sf::Vector3f mainFrameCoords; // Left, Top, Right
	float mainFrameWidth;
	float mainFrameBottom;
	float paddlePositionY;
	sf::Color frameColor;
	

	int windowWidth{ 1800 }, windowHeight{ 1200 };
	sf::RenderWindow* window;

	std::vector<Ball*> balls;
	float ballSize{ 25 };

	Paddle* paddle;
	sf::Vector2f paddleSize{ 150.f, 10.f };

	std::vector<std::vector<Block*>> blocks;
	int blocksCols{ 10 };
	int blocksRows{ 3 };
	int blockCount;
	int blockDist{ 10 };
	float blockWidth;
	float blockHight;

	int playerPoints{ 0 };
	int playerLives{ 2 };

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
	bool intersection(Ball* ball, int counter);

	void pollEvent();
	void update();
	void updateGui();
	void updateGameText();


	void renderGui();
	void draw();
};

