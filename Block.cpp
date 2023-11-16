#include "Block.h"

void Block::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(this->shape, state);
}

Block::Block(float x, float y){
	this->initBlock(x, y);
}

void Block::initBlock(float x, float y){

	this->shape.setSize(this->blockSize);
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setPosition(x, y);
	this->shape.setOrigin(this->blockSize.x / 2, this->blockSize.y / 2);
}

sf::FloatRect Block::getBoundary(){
	return this->shape.getGlobalBounds();
}
