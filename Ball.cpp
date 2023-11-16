#include "Ball.h"

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape, state);
}

Ball::Ball(sf::Vector2f movementVec)
{
	shape.setPosition(65.f, 300.f);
	shape.setRadius(this->ballRadius);
	shape.setFillColor(sf::Color::White);
	this->velocity = velocity;
	this->ballMovement = movementVec;
	shape.setOrigin(this->ballRadius, this->ballRadius);
}

Ball::Ball(float x, float y):
	Ball::Ball(sf::Vector2f {x,y}){
}
Ball::~Ball(){
	std::cout << "ballDestr\n";
}

void Ball::moveBall(){
	shape.move(this->velocity * this->ballMovement.x, this->velocity * this->ballMovement.y);
}


bool Ball::ballWindowCollision(sf::RenderTarget& window) {
	//Right & Left
	if (((this->shape.getPosition().x + static_cast<int>(this->ballRadius)) >= window.getSize().x) ||
		((this->shape.getPosition().x - this->ballRadius) <= 0))
		this->changeDirection(-1, 1);
	//Top 
	if ((this->shape.getPosition().y - this->ballRadius) <= 0)
		this->changeDirection(1, -1);
	//Bottom
	else if ((this->shape.getPosition().y + this->ballRadius) > window.getSize().y) {
		this->changeDirection(1, -1);
		return false;
	}
	return true;

}

void Ball::changeDirection(float x, float y){
	this->ballMovement.x *= x;
	this->ballMovement.y *= y;
}

bool Ball::ballPaddleCollision(sf::FloatRect paddle){
	//if bottome of ball is on the same lvl or bellow as paddle
	if (
		((this->shape.getPosition().y + this->ballRadius) >= paddle.top) &&
		((this->shape.getPosition().y) <= paddle.top) &&
		((this->shape.getPosition().x) >= paddle.left) && 
		((this->shape.getPosition().x) <= (paddle.left + paddle.width) )) {
			this->changeDirection(1, -1);
		}

	

	return false;
}

//temp func
sf::Vector2f Ball::getposition() {
	return this->shape.getPosition();
}

sf::FloatRect Ball::getBoundary()
{
	return this->shape.getGlobalBounds();
}
