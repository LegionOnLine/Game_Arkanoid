#include "Ball.h"

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape, state);
}
Ball::Ball(float alpha, sf::Vector2f possition, float size, float velocity) {
	shape.setPointCount(72); //use point every 5degree for ball drawing/callcuclating
	recalcAlpha(alpha);
	calcMovementVector(this->alpha);
	this->ballRadius = size;
	shape.setRadius(this->ballRadius);
	shape.setFillColor(sf::Color::White);
	this->velocity = velocity;
	shape.setOrigin(this->ballRadius, this->ballRadius);
	shape.setPosition(possition.x, possition.y);// -this->ballRadius);
	this->distanceLeftToMove = this->velocity;

	this->ballStuck = true;
	this->lostBall = false;
}
/*
Ball::Ball(sf::Vector2f movementVec, sf::Vector2f possition, float size, float velocity)
{
	this->velocity = velocity;
	this->ballRadius = size;
	shape.setRadius(this->ballRadius);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(this->ballRadius, this->ballRadius);
	shape.setPosition(possition.x, possition.y - this->ballRadius);

	this->ballStuck = true;
	this->lostBall = false;
}

Ball::Ball(float x, float y, sf::Vector2f possition, float size, float velocity):
	Ball::Ball(sf::Vector2f {x,y}, possition, size, velocity){
}
*/
Ball::~Ball(){
	std::cout << "ballDestr\n";
}
void Ball::restoreMovement() {
	this->distanceLeftToMove = this->velocity;
}
float Ball::getBallRadius(){
	return this->ballRadius;
}
float Ball::getDistanceLeftToMove() {
	return this->distanceLeftToMove;
}

void Ball::calcMovementVector(float alpha){
	this->ballMovementVector.x = std::cos(alpha * 3.14159 / 180);
	this->ballMovementVector.y = std::sin((alpha+180.f) * 3.14159 / 180);
	//std::cout << "alfa: " << alpha << " - [" << this->ballMovementVector.x << "," << this->ballMovementVector.y << std::endl;
	//std::cout << std::acos(this->ballMovementVector.x) * 180 / 3.1415 << std::endl;
}

void Ball::recalcAlpha(float alpha) {
	while (alpha >= 360.f) {
		alpha -= 360.f;
	}
	while (alpha < 0.f) {
		alpha += 360.f;
	}
	if (alpha == 0.f || alpha == 90.f || alpha == 180.f || alpha == 270.f) { alpha += 1.f; }
	this->alpha= alpha;
	if (this->alpha < 90.f) {
		this->direction = 0x10; // [0xXY]
	}
	else if (this->alpha < 180.f) {
		this->direction = 0x00;
	}
	else if (this->alpha < 270.f) {
		this->direction = 0x01;
	}
	else {
		this->direction = 0x11;
	}
}

//void Ball::moveBall(){ //to be removed?
//	if (!this->ballStuck) {
//		shape.move(this->distanceLeftToMove * this->ballMovementVector.x, this->distanceLeftToMove * this->ballMovementVector.y);
//		this->distanceLeftToMove = 0;
//	}
//}
void Ball::moveBall(float distance) {
	if (!this->ballStuck || this->distanceLeftToMove <= 0) {
		float dist{ distance > this->distanceLeftToMove ? this->distanceLeftToMove : distance };
		shape.move(dist * this->ballMovementVector.x, dist * this->ballMovementVector.y);
		this->distanceLeftToMove -= dist;
	}
}

//collisions

//bool Ball::ballLost(float outOfScreen) {
//	//Bottom
//	if ((this->shape.getPosition().y + this->ballRadius) > outOfScreen) {
//		return true;
//	}
//	return false;
//}

//bool Ball::ballFrameCollision(sf::Vector3f& frame) {
//	//Right & Left
//	if (((this->shape.getPosition().x - this->ballRadius) < frame.x) || // Left side
//		((this->shape.getPosition().x + this->ballRadius) > frame.z))	// Right side
//		this->changeDirection(-1, 1);
//	//Top 
//	if ((this->shape.getPosition().y - this->ballRadius) <= frame.y)	// Top side
//		this->changeDirection(1, -1);
//	//Bottom
//	return true;
//}

//bool Ball::ballPaddleCollision(sf::FloatRect paddle){
//	//if bottome of ball is on the same lvl or bellow as paddle
//	if (
//		((this->shape.getPosition().y + this->ballRadius) >= paddle.top) &&
//		((this->shape.getPosition().y) <= paddle.top) &&
//		((this->shape.getPosition().x) >= paddle.left) && 
//		((this->shape.getPosition().x) <= (paddle.left + paddle.width) )) {
//			this->changeDirection(1, -1);
//		}
//	return false;
//}

void Ball::changeDirection(float x, float y) {
	this->ballMovementVector.x *= x;
	this->ballMovementVector.y *= y;
}

void Ball::changeDirection(float beta) {
	recalcAlpha(this->alpha + beta);
	calcMovementVector(this->alpha);
}

//ball status
bool Ball::isBallStuck() {
	return this->ballStuck;
}
void Ball::ballRelease() {
	if (this->ballStuck) this->ballStuck = false;
}
void Ball::ballGetStuck() {
	this->ballStuck = true;
	this->restoreMovement();
}


//temp func
sf::FloatRect Ball::getBoundary() {
	return this->shape.getGlobalBounds();
	//return this->shape.getLocalBounds();
}

sf::Vector2f Ball::getposition() {
	//std::cout << shape.getPosition().x << " ";
	//std::cout << shape.getPosition().y << std::endl;
	return this->shape.getPosition();
}

float Ball::getSize(){
	return this->ballRadius;
}

//void Ball::ballLost(){
//	this->lostBall = true;
//}

bool Ball::getLostBall(){
	return this->lostBall;
}

float Ball::getBallAlfa(){
	return this->alpha;
}
int Ball::getBallDirection() {
	return this->direction;
}

float Ball::getBallVelocity(){
	return this->velocity;
}

sf::Vector2f Ball::getBallMovementVector() {
	return sf::Vector2f{
		this->velocity * this->ballMovementVector.x,
		this->velocity * this->ballMovementVector.y };
}

sf::Vector2f Ball::predictPosition() {

	//std::cout << this->distanceLeftToMove * this->ballMovementVector.y << std::endl;
	//std::cout <<"distanceLeftToMove" << this->distanceLeftToMove  << std::endl;
	//
	//std::cout << "ballMovementVector.x" << this->ballMovementVector.x << std::endl;
	//
	//std::cout << "ballMovementVector.y" << this->ballMovementVector.y << std::endl;
	//
	//std::cout << this->distanceLeftToMove * this->ballMovementVector.x << " ";
	return sf::Vector2f(
		this->shape.getPosition().x + this->distanceLeftToMove * this->ballMovementVector.x,
		this->shape.getPosition().y + this->distanceLeftToMove * this->ballMovementVector.y);
}
sf::Vector2f Ball::predictPosition(float distance) {

	//std::cout << this->distanceLeftToMove * this->ballMovementVector.y << std::endl;
	//std::cout <<"distanceLeftToMove" << this->distanceLeftToMove  << std::endl;
	//
	//std::cout << "ballMovementVector.x" << this->ballMovementVector.x << std::endl;
	//
	//std::cout << "ballMovementVector.y" << this->ballMovementVector.y << std::endl;
	//
	//std::cout << this->distanceLeftToMove * this->ballMovementVector.x << " ";
	return sf::Vector2f(
		this->shape.getPosition().x + distance * this->ballMovementVector.x,
		this->shape.getPosition().y + distance * this->ballMovementVector.y);
}