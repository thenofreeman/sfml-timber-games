#pragma once

#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player();

        void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
        void resetPlayerStats();
        bool hit(sf::Time timeHit);

        sf::Time getLastHitTime();
        sf::FloatRect getPosition();
        sf::Vector2f getCenter();
        float getRotation();
        sf::Sprite getSprite();
        int getHealth();

        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

        void stopLeft();
        void stopRight();
        void stopUp();
        void stopDown();

        void update(float elapsedTime, sf::Vector2i mousePosition);

        void upgradeSpeed();
        void upgradeHealth();
        void increaseHealthLevel(int amount);

    private:
        const float START_SPEED = 200;
        const float START_HEALTH = 100;
        sf::Vector2f position;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f resolution;
        sf::IntRect arena;
        int tilesize;

        bool upPressed;
        bool downPressed;
        bool leftPressed;
        bool rightPressed;

        int health;
        int maxHealth;
        sf::Time lastHit;

        float speed;
};
