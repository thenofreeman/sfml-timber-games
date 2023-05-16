#include <iostream>
#include <SFML/Graphics.hpp>

int main(/*int argc, char *argv[]*/)
{
    sf::RenderWindow window (sf::VideoMode(1920,1080), "SFML Works!");

    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    spriteBackground.setPosition(0,0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(spriteBackground);
        window.display();
    }

    return 0;
}
