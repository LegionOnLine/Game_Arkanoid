#pragma once
#include <SFML/Graphics.hpp>

class Block : public sf::Drawable{
private:
	sf::RectangleShape shape;
	sf::Vector2f blockSize{ 60,20 };

public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	Block(float x, float y);
	virtual ~Block() = default;


	void initBlock(float x, float y);
	sf::FloatRect getBoundary();

};

