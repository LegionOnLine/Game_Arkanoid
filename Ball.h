#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Ball : public sf::Drawable{
private:
	sf::CircleShape shape;
	float alpha; //[0-360)
	int direction; // [1-4]
	sf::Vector2f ballMovementVector; // x,y : [-1 - +1]
	float velocity{ 1 };
	float distanceLeftToMove;// { velocity };

	bool ballStuck;
	bool lostBall;
	float ballRadius;

public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	Ball(float alfa, sf::Vector2f possition, float size, float velocity);
	Ball() = delete;
	~Ball();

	//Ball(sf::Vector2f movementVec, sf::Vector2f possition, float size, float velocity);
	//Ball(float x, float y, sf::Vector2f possition, float size, float velocity);
	

	//calculate ballMovementVector - x/y coords depending on angle
	void calcMovementVector(float alpha);
	void recalcAlpha(float alpha);

	//void moveBall(); //to be removed?
	void moveBall(float distance);


	//collisions
	//bool ballLost(float y);
	//bool ballFrameCollision(sf::Vector3f& frame);
	//bool ballPaddleCollision(sf::FloatRect paddle);
	void changeDirection(float x, float y);
	void changeDirection(float beta);


	//ball status
	void restoreMovement();
	bool isBallStuck();
	void ballRelease();
	void ballGetStuck();
	//void ballLost();


	//temp func
	float getBallRadius();
	float getDistanceLeftToMove();
	sf::FloatRect getBoundary();
	sf::Vector2f getposition();
	float getSize();
	bool getLostBall();
	float getBallAlfa();
	int getBallDirection();
	float getBallVelocity();
	sf::Vector2f getBallMovementVector();

	sf::Vector2f predictPosition();
	sf::Vector2f predictPosition(float distance);
};

