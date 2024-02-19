#pragma once
#include <SFML/Graphics.hpp>

class Bat
{
protected:



public:
	float speed = 100.f;
	sf::RectangleShape shape;

	void Init();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

