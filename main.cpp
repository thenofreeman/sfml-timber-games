#include <iostream>
#include <sstream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Bat.h"

int main()
{
    sf::RenderWindow window (sf::VideoMode(1920, 1080), "Pong");

    int score = 0;
    int lives = 3;

    Bat bat (1920 / 2, 1080 - 20);

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
        std::stringstream ss;
        ss << "Score: " << score << " Lives: " << lives;
        hud.setString(ss.str());

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
        window.display();
    }

    return 0;
}
