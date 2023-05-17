#include <iostream>
#include <sstream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Bat.h"
#include "Ball.h"

int main()
{
    sf::RenderWindow window (sf::VideoMode(1920, 1080), "Pong");

    int score = 0;
    int lives = 3;

    Bat bat (1920/2, 1080 - 20);
    Ball ball (1920/2, 0);

    sf::Text hud;

    sf::Font font;
    font.loadFromFile("fonts/digital-7-mono.ttf");

    hud.setFont(font);
    hud.setFillColor(sf::Color::White);
    hud.setPosition(20, 20);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        bat.update(dt);
        ball.update(dt);

        std::stringstream ss;
        ss << "Score: " << score << " Lives: " << lives;
        hud.setString(ss.str());

        if (ball.getPosition().top > window.getSize().y)
        {
            ball.reboundBottom();
            lives--;
            if (lives < 1)
            {
                score = 0;
                lives = 3;
            }
        }

        if (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();
            score++;
        }

        if (ball.getPosition().left < 0 ||
            (ball.getPosition().left + ball.getPosition().width) > window.getSize().x)
        {
            ball.reboundBatOrTop();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                bat.moveLeft();
            else
                bat.stopLeft();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                bat.moveRight();
            else
                bat.stopRight();
        }

        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }

    return 0;
}
