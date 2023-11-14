#include "Ball.h"
#include <iostream>

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape, state);
}

Ball::Ball()
{
	shape.setPosition(60.f, 60.f);
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::White);
	this->velocity = velocity;
	//shape.setOrigin(this->ballRadius, this->ballRadius);
}

void Ball::moveBall(float x, float y){
	shape.move((this->velocity*(x > 1 ? 1 : (x < -1 ? -1 : x))), (this->velocity * (y > 1 ? 1 : (y < -1 ? -1 : y))));
}

void Ball::move(sf::Vector2f){
}
