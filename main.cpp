#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

void updateBranches(const int& seed);
const int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

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

    struct SpriteCloud
    {
        sf::Sprite sprite;
        bool active;
        float speed;
    };

    SpriteCloud spriteClouds[3];

    int yOffset = 0;
    for (SpriteCloud& sc : spriteClouds)
    {
        sc.sprite.setTexture(textureCloud);
        sc.sprite.setPosition(-400, yOffset);
        sc.active = false;
        sc.speed = 0.0f;

        yOffset += 250;
    }

    sf::Clock clock;

    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition((1920/2) - timeBarStartWidth / 2, 980);
    sf::Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

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

    sf::Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    for (sf::Sprite& branch : branches)
    {
        branch.setTexture(textureBranch);
        branch.setPosition(-2000, -2000);
        branch.setOrigin(220, 20);
    }

    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    side playerSide = side::LEFT;

    sf::Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    sf::Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    sf::Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    sf::Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    sf::Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    sf::Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    bool acceptInput = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyReleased && !paused)
            {
                acceptInput = true;

                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Return)
                {
                    paused = !paused;
                    score = 0;
                    timeRemaining = 6.0f;

                    for (int i = 1; i < NUM_BRANCHES; i++)
                        branchPositions[i] = side::NONE;

                    spriteRIP.setPosition(675, 2000);
                    spritePlayer.setPosition(580, 720);
                    acceptInput = true;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (acceptInput)
                    {
                        playerSide = side::RIGHT;

                        score++;

                        timeRemaining += (2/score) + 0.15;
                        spriteAxe.setPosition(AXE_POSITION_RIGHT,
                                            spriteAxe.getPosition().y);
                        spritePlayer.setPosition(1200, 720);

                        updateBranches(score);

                        spriteLog.setPosition(810, 720);
                        logSpeedX = -5000;
                        logActive = true;
                        acceptInput = false;
                    }
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (acceptInput)
                    {
                        playerSide = side::LEFT;

                        score++;

                        timeRemaining += (2/score) + 0.15;
                        spriteAxe.setPosition(AXE_POSITION_LEFT,
                                            spriteAxe.getPosition().y);
                        spritePlayer.setPosition(580, 720);

                        updateBranches(score);

                        spriteLog.setPosition(810, 720);
                        logSpeedX = 5000;
                        logActive = true;
                        acceptInput = false;
                    }
                }
            }
        }

        sf::Time dt = clock.restart();

        if (!paused)
        {
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining,
                                         timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                paused = true;
                messageText.setString("Out of time!");

                sf::FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                      textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

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

            int speedOffset = 10;
            int heightOffset = 150;
            for (SpriteCloud& sc : spriteClouds)
            {
                if (!sc.active)
                {
                    srand((int) time(0) * speedOffset);
                    sc.speed = (rand() % 200);
                    srand((int) time(0) * speedOffset);
                    float height = (rand() % heightOffset) + 150;
                    sc.sprite.setPosition(-400, height);
                    sc.active = true;

                    speedOffset += 10;
                    heightOffset += 150;
                }
                else
                {
                    sc.sprite.setPosition(
                        sc.sprite.getPosition().x + (sc.speed * dt.asSeconds()),
                        sc.sprite.getPosition().y
                    );
                    if (sc.sprite.getPosition().x > 1920)
                        sc.active = false;
                }

            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            for (int i = 0; i < NUM_BRANCHES; ++i)
            {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT)
                {
                    branches[i].setPosition(610, height);
                    branches[i].setRotation(180);
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                }
                else
                {
                    branches[i].setPosition(3000, height);
                }
            }

            if (logActive)
            {
                spriteLog.setPosition(
                    spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                    spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
                                      );
                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
                {
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }

            if (branchPositions[5] == playerSide)
            {
                paused = true;
                acceptInput = false;
                spriteRIP.setPosition(525, 760);
                spritePlayer.setPosition(2000, 660);
                messageText.setString("OUCH!!");
                sf::FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                      textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920/2.0f, 1080/2.0f);
            }
        }

        window.clear();

        window.draw(spriteBackground);
        for (SpriteCloud& sc : spriteClouds)
            window.draw(sc.sprite);

        for (sf::Sprite& branch : branches)
            window.draw(branch);

        window.draw(spriteTree);

        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRIP);

        window.draw(spriteBee);

        window.draw(timeBar);

        window.draw(scoreText);
        if (paused)
        {
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}

void updateBranches(const int& seed)
{
    for (int j = NUM_BRANCHES-1; j > 0; --j)
        branchPositions[j] = branchPositions[j - 1];

    srand((int) time(0) + seed);
    int r = (rand() % 5);

    switch (r)
    {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}
