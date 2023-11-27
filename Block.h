#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Block : public sf::Drawable{
private:
	sf::RectangleShape shape;
	sf::Vector2f blockSize{ 60,20 };
	bool printable{ true };
	int points{ 1 };

public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	Block(float x, float y, float w, float h);
	virtual ~Block();


	void initBlock(float x, float y, float w, float h);
	sf::FloatRect getBoundary();
	sf::Vector2f getBlockSize();
	bool printableObj();
	bool changeState();
	int getPoints();

};

