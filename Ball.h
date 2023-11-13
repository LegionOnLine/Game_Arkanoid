#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable{
private:
	sf::CircleShape shape;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;

	Ball();
	~Ball() = default;


};

