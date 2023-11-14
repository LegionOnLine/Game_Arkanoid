#pragma once
#include <SFML/Graphics.hpp>


class Paddle : public sf::Drawable{
private:
	float positionY{ 500 };
	sf::Vector2f paddleSize{ 50.f, 10.f };
	sf::RectangleShape paddle;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;

	Paddle();
	~Paddle() = default;

	void initPaddle();
};

