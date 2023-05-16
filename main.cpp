#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

int main(/*int argc, char *argv[]*/)
{
    sf::RenderWindow window (sf::VideoMode(1920, 1080), "SFML Works!");

    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    spriteBackground.setPosition(0, 0);

    sf::Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    sf::Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(-100, 800);

    bool beeActive = false;
    float beeSpeed = 0.0f;

    sf::Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    sf::Sprite spriteCloud1;
    sf::Sprite spriteCloud2;
    sf::Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    spriteCloud1.setPosition(-400, 0);
    spriteCloud2.setPosition(-400, 250);
    spriteCloud3.setPosition(-400, 500);

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    sf::Clock clock;

    int score = 0;

    bool paused = true;

    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    sf::Text messageText;
    sf::Text scoreText;

    messageText.setFont(font);
    scoreText.setFont(font);

    messageText.setString("Pres Enter to Start!");
    messageText.setCharacterSize(75);
    messageText.setFillColor(sf::Color::White);

    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080/2.0f);
    scoreText.setPosition(20, 20);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Return)
                    paused = !paused;
        }

        sf::Time dt = clock.restart();

        if (!paused)
        {

            if (!beeActive)
            {
                srand((int) time(0));
                beeSpeed = (rand() % 200) + 200;
                srand((int) time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                spriteBee.setPosition(
                    spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y
                );
                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            if (!cloud1Active)
            {
                srand((int) time(0) * 10);
                cloud1Speed = (rand() % 200);
                srand((int) time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-400, height);
                cloud1Active = true;
            }
            else
            {
                spriteCloud1.setPosition(
                    spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
                    spriteCloud1.getPosition().y
                );
                if (spriteCloud1.getPosition().x > 1920)
                    cloud1Active = false;
            }

            if (!cloud2Active)
            {
                srand((int) time(0) * 20);
                cloud2Speed = (rand() % 200);
                srand((int) time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(-400, height);
                cloud2Active = true;
            }
            else
            {
                spriteCloud2.setPosition(
                    spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
                    spriteCloud2.getPosition().y
                );
                if (spriteCloud2.getPosition().x > 1920)
                    cloud2Active = false;
            }

            if (!cloud3Active)
            {
                srand((int) time(0) * 30);
                cloud3Speed = (rand() % 200);
                srand((int) time(0) * 20);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-400, height);
                cloud3Active = true;
            }
            else
            {
                spriteCloud3.setPosition(
                    spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
                    spriteCloud3.getPosition().y
                );
                if (spriteCloud3.getPosition().x > 1920)
                    cloud3Active = false;
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        window.draw(spriteTree);
        window.draw(spriteBee);

        window.draw(scoreText);
        if (paused)
        {
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}
