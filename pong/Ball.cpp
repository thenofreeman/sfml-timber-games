#include "Ball.h"

Ball::Ball(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    shape.setSize(sf::Vector2f(10, 10));
    shape.setPosition(position);
}

sf::FloatRect Ball::getPosition()
{
    return shape.getGlobalBounds();
}

sf::RectangleShape Ball::getShape()
{
    return shape;
}

float Ball::getXVelocity()
{
    return directionX;
}

void Ball::reboundSides()
{
    directionX = -directionX;
}

void Ball::reboundBatOrTop()
{
    directionY = -directionY;
}

void Ball::reboundBottom()
{
    position.y = 0;
    position.x = 500;
    directionY = -directionY;
}

void Ball::update(sf::Time dt)
{
    position.y += directionY * speed * dt.asSeconds();
    position.x += directionX * speed * dt.asSeconds();

    shape.setPosition(position);
}
