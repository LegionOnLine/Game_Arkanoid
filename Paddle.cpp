#include "Paddle.h"
#include <iostream>
void Paddle::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(this->paddle, state);
}

Paddle::Paddle(float frameX, float frameY){
	this->paddle.setSize(this->paddleSize);
	this->paddle.setFillColor(sf::Color::Green);
	this->paddle.setOrigin(this->paddleSize.x/2, this->paddleSize.y/2);
	this->paddle.setPosition(frameX, frameY);

	//std::cout << this->paddle.getPosition().x;
	this->hp = 3;
	this->holdingBall = true;
}


void Paddle::paddleWindowCollision(sf::RenderTarget& window){
	if (this->paddle.getPosition().x - this->paddleSize.x/2 < 0)
		this->paddle.setPosition(this->paddleSize.x/2, this->paddle.getPosition().y);
	else if (this->paddle.getPosition().x + this->paddleSize.x/2 > window.getSize().x)
		this->paddle.setPosition(window.getSize().x - this->paddleSize.x/2, this->paddle.getPosition().y);
}

void Paddle::paddleFrameCollision(sf::Vector3f frame){
	if (this->paddle.getPosition().x - this->paddleSize.x / 2 < frame.x)
		this->paddle.setPosition(frame.x + this->paddleSize.x / 2, this->paddle.getPosition().y);
	else if (this->paddle.getPosition().x + this->paddleSize.x / 2 > frame.z)
		this->paddle.setPosition(frame.z - this->paddleSize.x / 2, this->paddle.getPosition().y);
}

void Paddle::paddleMove(int x){
	if (x > 0) this->paddle.move(this->paddleSpeed, 0.f);
	else this->paddle.move(-this->paddleSpeed, 0.f);

}

sf::FloatRect Paddle::getBoundary(){
	return this->paddle.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition(){
	return this->paddle.getPosition();
}
