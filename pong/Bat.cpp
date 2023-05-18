#include "Bat.h"

Bat::Bat(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    shape.setSize(sf::Vector2f(50, 5));
    shape.setPosition(position);
}

sf::FloatRect Bat::getPosition()
{
    return shape.getGlobalBounds();
}

sf::RectangleShape Bat::getShape()
{
    return shape;
}

void Bat::moveLeft()
{
    movingLeft = true;
}

void Bat::moveRight()
{
    movingRight = true;
}

void Bat::stopLeft()
{

    movingLeft = false;
}

void Bat::stopRight()
{

    movingRight = false;
}

void Bat::update(sf::Time dt)
{
    if (movingLeft)
        position.x -= speed * dt.asSeconds();
    else
        position.x += speed * dt.asSeconds();

    shape.setPosition(position);
}
