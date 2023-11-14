#include "Ball.h"
#include <iostream>

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape, state);
}

Ball::Ball(sf::Vector2f movementVec)
{
	shape.setPosition(60.f, 60.f);
	shape.setRadius(this->ballRadius);
	shape.setFillColor(sf::Color::White);
	this->velocity = velocity;
	this->ballMovement = movementVec;
	shape.setOrigin(this->ballRadius, this->ballRadius);
}

Ball::Ball(float x, float y):
	Ball::Ball(sf::Vector2f {x,y}){
}

void Ball::moveBall(){
	shape.move(this->velocity * this->ballMovement.x, this->velocity * this->ballMovement.y);
	//shape.move((this->velocity*(x > 1 ? 1 : (x < -1 ? -1 : x))), (this->velocity * (y > 1 ? 1 : (y < -1 ? -1 : y))));
}


void Ball::ballWindowCollision(sf::RenderTarget& window) {
	//Right & Left
	if (((this->shape.getPosition().x + static_cast<int>(this->ballRadius)) >= window.getSize().x) ||
		((this->shape.getPosition().x - this->ballRadius) <= 0))
		this->changeDirection(-1, 1);
	//Top & Bottom
	if (((this->shape.getPosition().y + this->ballRadius) > window.getSize().y) ||
		((this->shape.getPosition().y - this->ballRadius) <= 0))
		this->changeDirection(1, -1);

}

void Ball::changeDirection(float x, float y){
	this->ballMovement.x *= x;
	this->ballMovement.y *= y;
}
sf::Vector2f Ball::getposition() {
	return this->shape.getPosition();
}