#include "Player.h"

Player::Player()
{
    speed = START_SPEED;
    health = START_HEALTH;
    maxHealth = START_HEALTH;

    texture.loadFromFile("graphics/player.png");
    sprite.setTexture(texture);
    sprite.setOrigin(25, 25);
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
    position.x = arena.width/2;
    position.y = arena.height/2;

    this->arena.left = arena.left;
    this->arena.width = arena.width;
    this->arena.top = arena.top;
    this->arena.height = arena.height;

    this->tileSize = tileSize;

    this->resolution.x = resolution.x;
    this->resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
    speed = START_SPEED;
    health = START_HEALTH;
    maxHealth = START_HEALTH;
}

sf::Time Player::getLastHitTime()
{
    return lastHit;
}

bool Player::hit(sf::Time timeHit)
{
    if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > 200)
    {
        lastHit = timeHit;
        health -= 10;

        return true;
    }
    else
    {
        return false;
    }
}

sf::FloatRect Player::getPosition()
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Player::getCenter()
{
    return position;
}

float Player::getRotation()
{
    return sprite.getRotation();
}

sf::Sprite Player::getSprite()
{
    return sprite;
}

int Player::getHealth()
{
    return health;
}

void Player::moveLeft()
{
    leftPressed = true;
}

void Player::moveRight()
{
    rightPressed = true;
}

void Player::moveUp()
{
    upPressed = true;
}

void Player::moveDown()
{
    downPressed = true;
}

void Player::stopLeft()
{
    leftPressed = false;
}

void Player::stopRight()
{
    rightPressed = false;
}

void Player::stopUp()
{
    upPressed = false;
}

void Player::stopDown()
{
    downPressed = false;
}

void Player::update(float elapsedTime, sf::Vector2i mousePosition)
{
    if (upPressed)
    {
        position.y -= speed * elapsedTime;
    }

    if (downPressed)
    {
        position.y += speed * elapsedTime;
    }

    if (rightPressed)
    {
        position.x += speed * elapsedTime;
    }

    if (leftPressed)
    {
        position.x -= speed * elapsedTime;
    }

    sprite.setPosition(position);

    if (position.x > arena.width -tileSize)
    {
        position.x = arena.width -tileSize;
    }

    if (position.x < arena.left + tileSize)
    {
        position.x = arena.left + tileSize;
    }

    if (position.y > arena.height - tileSize)
    {
        position.y = arena.height - tileSize;
    }

    if (position.y < arena.top + tileSize)
    {
        position.y = arena.top + tileSize;
    }

    float angle = (sf::atan2(mousePosition.y - resolution.y / 2,
                             mousePosition.x - resolution.x / 2)
                   * 180) / 3.141;

    sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
    speed += (START_SPEED * 0.2);
}

void Player::upgradeHealth()
{
    maxHealth += (START_HEALTH * 0.2);
}

void Player::increaseHealthLevel(int amount)
{
    health += amount;

    if (health > maxHealth)
    {
        health = maxHealth;
    }
}
