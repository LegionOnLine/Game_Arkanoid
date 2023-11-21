#include "Paddle.h"

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(this->paddle, state);
}

Paddle::Paddle(float frameX){
	this->initPaddle();
	this->paddle.setPosition(frameX / 2, this->positionY);
}

void Paddle::initPaddle(){
	this->paddle.setSize(this->paddleSize);
	this->paddle.setFillColor(sf::Color::Green);
	//this->paddle.setPosition(50.f, this->positionY);
	this->paddle.setOrigin(this->paddleSize.x/2, this->paddleSize.y/2);
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
