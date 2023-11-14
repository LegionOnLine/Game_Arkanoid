#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable{
private:
	sf::CircleShape shape;
	sf::Vector2f ballMovement;

	float velocity{ 1 };
	float ballRadius{ 5.f };

public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;

	Ball(sf::Vector2f movementVec);
	Ball(float x, float y);
	Ball() = delete;
	~Ball() = default;

	void moveBall();

	void ballWindowCollision(sf::RenderTarget& window);
	void changeDirection(float x, float y);

};

