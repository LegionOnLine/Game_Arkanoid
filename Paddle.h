#pragma once
#include <SFML/Graphics.hpp>


class Paddle : public sf::Drawable{
private:
	float paddleSpeed{ 15 };
	float positionY{ 500 };
	sf::Vector2f paddleSize{ 100.f, 10.f };
	sf::RectangleShape paddle;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	Paddle() = delete;
	Paddle(float frameX);
	~Paddle() = default;

	void initPaddle();
	void paddleWindowCollision(sf::RenderTarget& window);
	void paddleFrameCollision(sf::Vector3f frame);
	void paddleMove(int x);
	sf::FloatRect getBoundary();
};

