#pragma once

#include <SFML/Graphics.hpp>

class Bat
{
    public:
        Bat(float startX, float startY);

        sf::FloatRect getPosition();
        sf::RectangleShape getShape();

        void moveLeft();
        void moveRight();
        void stopLeft();
        void stopRight();
        void update(sf::Time dt);

    private:
        sf::Vector2f position;
        sf::RectangleShape shape;
        float speed = 1000.0f;
        bool movingRight = false;
        bool movingLeft = false;

};
