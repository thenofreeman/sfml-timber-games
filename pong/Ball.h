#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
    public:
        Ball(float startX, float startY);
        sf::FloatRect getPosition();

        sf::RectangleShape getShape();
        float getXVelocity();

        void reboundSides();
        void reboundBatOrTop();
        void reboundBottom();
        void update(sf::Time dt);

    private:
        sf::Vector2f position;
        sf::RectangleShape shape;
        float speed = 300.0f;
        float directionX = 0.2f;
        float directionY = 0.2f;

};
