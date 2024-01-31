#include "Block.h"

int Block::i = 0;

void Block::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(this->shape, state);
}

Block::Block(float x, float y, float w, float h, int hp, sf::Color c){
	this->initBlock(x, y, w, h, hp, c);
}

Block::~Block(){
	//std::cout << "xBlock\n";
}

void Block::initBlock(float x, float y, float w, float h, int hp, sf::Color c){
	this->blockSize = sf::Vector2f{ w,h};
	this->undestr = (hp == -1) ? true : false;
	this->shape.setSize(this->blockSize);
	this->shape.setFillColor(c);
	if (hp != -1) this->shape.setOrigin(w / 2, h / 2);

	this->shape.setPosition(x, y);
	this->shape.setOutlineColor(sf::Color::White);
	this->shape.setOutlineThickness((hp != -1) ? 1.f : 0.f);
	this->hpMax = hp;
	this->hp = this->hpMax;
	this->points = hp;
	++i;
	std::cout << i << std::endl;
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

int Block::getPoints(){
	return this->points;
}
void Block::setcolor(sf::Color nc) {
	this->shape.setFillColor(nc);
}