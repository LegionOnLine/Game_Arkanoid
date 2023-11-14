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
	this->paddle.setOrigin(this->paddleSize.x/2, this->paddleSize.y/2);
}

void Paddle::paddleMove(int x){
	if (x > 0) this->paddle.move(this->paddleSpeed, 0.f);
	else this->paddle.move(-this->paddleSpeed, 0.f);

}

sf::FloatRect Paddle::getBoundary(){
	return this->paddle.getGlobalBounds();
}
