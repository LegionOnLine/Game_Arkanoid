#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ball : public sf::Drawable{
private:
	sf::CircleShape shape;
	sf::Vector2f ballMovement;

	float velocity{ 2 };
	float ballRadius{ 25.f };

public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;

	Ball(sf::Vector2f movementVec);
	Ball(float x, float y);
	Ball() = delete;
	~Ball();

	void moveBall();

	bool ballWindowCollision(sf::RenderTarget& window);
	bool ballPaddleCollision(sf::FloatRect paddle);
	void changeDirection(float x, float y);

	sf::FloatRect getBoundary();
	//temp func
	sf::Vector2f getposition();
};

