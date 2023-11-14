#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable{
private:
	sf::CircleShape shape;
	float velocity{ 1 };
public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;

	Ball();
	~Ball() = default;

	void moveBall(float x, float y);
	void move(sf::Vector2f);
};

