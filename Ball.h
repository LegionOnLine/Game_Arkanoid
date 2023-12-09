#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Ball : public sf::Drawable{
private:
	sf::CircleShape shape;
	float alpha;
	sf::Vector2f ballMovementVector; // x,y : [-1 - +1]
	float velocity{ 1 };

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
	

	void calcMovementVector(float alpha);
	void recalcAlpha(float alpha);

	void moveBall();

	bool ballWindowCollision(sf::RenderTarget& window);

	bool ballLost(float y);
	bool ballFrameCollision(sf::Vector3f& frame);
	

	bool ballPaddleCollision(sf::FloatRect paddle);
	void changeDirection(float x, float y);
	void changeDirection(float beta);

	bool isBallStuck();
	void ballRelease();

	sf::FloatRect getBoundary();
	//temp func
	sf::Vector2f getposition();
	float getSize();
	void ballLost();
	bool getLostBall();
};

