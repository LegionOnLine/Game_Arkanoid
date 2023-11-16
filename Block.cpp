#include "Block.h"

void Block::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(this->shape, state);
}

Block::Block(float x, float y, float w, float h){
	this->initBlock(x, y, w, h);
}

Block::~Block(){
	std::cout << "xBlock\n";
}

void Block::initBlock(float x, float y, float w, float h){
	this->blockSize = sf::Vector2f{ w,h};
	this->shape.setSize(this->blockSize);
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setOrigin(w / 2, h / 2);
	this->shape.setPosition(x, y);
	this->shape.setOutlineColor(sf::Color::White);
	this->shape.setOutlineThickness(1.f);
}

sf::FloatRect Block::getBoundary(){
	return this->shape.getGlobalBounds();
}

sf::Vector2f Block::getBlockSize(){
	return this->blockSize;
}

bool Block::printableObj(){
	return this->printable;
}

bool Block::changeState(){
	this->printable = false;
	return this->printable;
}
