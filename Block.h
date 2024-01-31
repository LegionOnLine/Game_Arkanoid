#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Block : public sf::Drawable{
private:
	sf::RectangleShape shape;
	sf::Vector2f blockSize{ 60,20 };
	bool printable{ true };
	bool undestr{ false };
	int hpMax;
	int hp;
	int points;
	static int i;

public:
	static int getId() {
		return i;
	};
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	Block(float x, float y, float w, float h, int hp, sf::Color c = sf::Color::Red);
	virtual ~Block();

	void initBlock(float x, float y, float w, float h, int hp, sf::Color c);
	sf::FloatRect getBoundary();
	sf::Vector2f getBlockSize();
	bool printableObj();
	bool changeState();
	int getPoints();

	void setcolor(sf::Color);
};

