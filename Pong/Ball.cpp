#include "pch.h"
#include "Ball.h"
#include "Bat.h"


Ball::Ball(Bat& b, const sf::FloatRect& bounds)
	:bat(b),windowBounds(bounds)
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::White);
	Utils::SetOrigin(shape, Origins::BC);
}

void Ball::Fire(sf::Vector2f d, float s)
{
	direction = d;
	speed = s;
	isDead = false;
}

void Ball::Update(float dt)
{
	isBoundBat = false;

	sf::Vector2f pos = shape.getPosition();
	pos += direction * speed * dt;
	shape.setPosition(pos);

	const sf::FloatRect& ballBounds = shape.getGlobalBounds();
	const sf::FloatRect& batBounds = bat.shape.getGlobalBounds();
	//충돌처리
	if (windowBounds.top > ballBounds.top )
	{
		if (windowBounds.top < ballBounds.top)
		{
			shape.setPosition(shape.getPosition().x, windowBounds.top + ballBounds.top + ballBounds.height);
		}
		direction.y *= -1;
	}
	if (windowBounds.left > ballBounds.left ||
		windowBounds.left + windowBounds.width < ballBounds.left + ballBounds.width)
	{
		direction.x *= -1;
	}

	if (ballBounds.intersects(batBounds))
	{
		if (ballBounds.top + ballBounds.height > batBounds.top)
		{
			shape.setPosition(pos);
		}
		direction *= -1.f;
		isBoundBat = true;
	}
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
