#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <set>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bouncing.h"


class Game {
private:


	int windowWidth{ 1800 }, windowHeight{ 1200 };
	sf::RenderWindow* window;


	//Text Objects
	sf::Font font;
	sf::Text textPoints;
	sf::Text textLives;
	sf::Text textGame;

	//Frame:
	sf::Color frameColor{sf::Color::Blue};
	float mainFrameWidth{ 10. };
	Block* leftWall;
	Block* topWall;
	Block* rightWall;


	std::vector<Block*> walls; // Left, Top, Right
	
	sf::VertexArray* mainFrame;
	sf::Vector3f mainFrameCoords; // Left, Top, Right
	float mainFrameBottom;

	float paddleLevel;

	std::vector<Ball*> balls;
	float ballSize{ 150/2 };
	float ballSpeed{ 550 };
	float alpha{90.0};

	Paddle* paddle;
	sf::Vector2f paddleSize{ 150.f, 10.f };

	std::vector<std::vector<Block*>> blocks;
	int blocksCols{ 10 };
	int blocksRows{ 3 };
	int blockCount;
	int blockDist{ 10 };
	float blockWidth;
	float blockHight;

	// <<left,top>, obj>
	std::map<std::pair<float,float>, Block*> mapBlock;
	

	int playerPoints{ 0 };
	int playerLives{ 2 };

	bool gameOver{ false };

public:

	sf::CircleShape p00, p01, p10, p11;
	sf::Vertex v0, v1, v2, v3;
	float r{ 2 };
	sf::RectangleShape range;
	

	bool stop{ false }; //tmp
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

	void colisionAlgorithm(Ball *ball);
	void colisionCheckPhase1X(Ball *ball, std::set<float> *rangeX, std::multimap<std::pair<float, float>, Block*> *secondMap, bool *secondAxis);
	void colisionCheckPhase1Y(Ball *ball, std::set<float> *rangeY, std::multimap<std::pair<float, float>, Block*> *secondMap, bool *secondAxis);
	float colisionCheckPhase2(Ball* ball, float endPositionX, float endPositionY, std::multimap<std::pair<float, float>, Block*>* secondMap, std::set<float>* rangeX, std::set<float>* rangeY);
	float collisionRespond(float alpha, char normalAxis);

	float calculateDistance(float x, float y, float a, float b);
	float calculateDistanceX(float xp, float yp, float xs, float ys, float yc);
	float calculateDistanceY(float xp, float yp, float xs, float ys, float xc);
	float calculateCoords(float startPositionX, float startPositionY, float endPositionX, float endPositionY, float collisionPositionX, float collisionPositionY);

	void update();
	void updateGui();
	void updateGameText();


	void renderGui();
	void draw();
};

