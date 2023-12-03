#pragma once
#include <SFML/Graphics.hpp>


class Paddle : public sf::Drawable{
private:
	float paddleSpeed{ 5 };
	//float positionY{ 100 };
	//sf::Vector2f paddleSize{ 1590.f, 10.f };
	sf::Vector2f paddleSize;// { 150.f, 10.f };
	sf::RectangleShape paddle;
	sf::RectangleShape paddleCenter;
	sf::RectangleShape paddleMidSideL;
	sf::RectangleShape paddleMidSideR;
	sf::RectangleShape paddleSide;

	float paddleCenterSize{ 0.6 };
	float paddleMidSize{ 0.2 };
	float paddleSideSize{ 0.2 };

	int hp{ 3 };
	bool holdingBall{ true };

public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	Paddle() = delete;
	Paddle(float frameX, float frameY, sf::Vector2f paddleSize);
	~Paddle() = default;

	void paddleWindowCollision(sf::RenderTarget& window);
	void paddleFrameCollision(sf::Vector3f frame);
	void paddleMove(int x);
	sf::FloatRect getBoundary();
	sf::Vector2f getPosition();
};

