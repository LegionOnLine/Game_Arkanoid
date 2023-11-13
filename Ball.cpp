#include "Ball.h"

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape, state);
}

Ball::Ball()
{
	shape.setPosition(60.f, 60.f);
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::White);
	//shape.setOrigin(this->ballRadius, this->ballRadius);
}
