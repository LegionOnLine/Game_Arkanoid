#include "Paddle.h"

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(this->paddle, state);
}

Paddle::Paddle(){
	this->initPaddle();
}

void Paddle::initPaddle(){
	this->paddle.setSize(this->paddleSize);
	this->paddle.setFillColor(sf::Color::Green);
	this->paddle.setPosition(50.f, this->positionY);
}
