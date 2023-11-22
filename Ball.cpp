#include "Ball.h"

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape, state);
}

Ball::Ball(sf::Vector2f movementVec, sf::Vector2f possition)
{
	shape.setPosition(possition.x, possition.y-this->ballRadius);
	shape.setRadius(this->ballRadius);
	shape.setFillColor(sf::Color::White);
	this->velocity = velocity;
	this->ballMovement = movementVec;
	shape.setOrigin(this->ballRadius, this->ballRadius);

	this->ballStuck = true;
}

Ball::Ball(float x, float y, sf::Vector2f possition):
	Ball::Ball(sf::Vector2f {x,y}, possition){
}
Ball::~Ball(){
	std::cout << "ballDestr\n";
}

void Ball::moveBall(){
	if (!this->ballStuck) {
		shape.move(this->velocity * this->ballMovement.x, this->velocity * this->ballMovement.y);
	}
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

bool Ball::ballLost(float outOfScreen) {
	//Bottom
	if ((this->shape.getPosition().y + this->ballRadius) > outOfScreen) {
		//this->changeDirection(1, -1);
		return true;
	}
	return false;
}

bool Ball::ballFrameCollision(sf::Vector3f& frame) {
	//Right & Left
	if (((this->shape.getPosition().x - this->ballRadius) < frame.x) || // Left side
		((this->shape.getPosition().x + this->ballRadius) > frame.z))	// Right side
		this->changeDirection(-1, 1);
	//Top 
	if ((this->shape.getPosition().y - this->ballRadius) <= frame.y)	// Top side
		this->changeDirection(1, -1);
	//Bottom
	return true;
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

void Ball::changeDirection(float x, float y) {
	this->ballMovement.x *= x;
	this->ballMovement.y *= y;
}

//temp func
sf::Vector2f Ball::getposition() {
	return this->shape.getPosition();
}


sf::FloatRect Ball::getBoundary()
{
	return this->shape.getGlobalBounds();
}

bool Ball::isBallStuck() {
	return this->ballStuck;
}
void Ball::ballRelease(){
	if (this->ballStuck) this->ballStuck = false;
}
