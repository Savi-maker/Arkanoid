#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "Paddle.h"
#include "Block.h"
#include "MainMenu.h"
#include "Poziom1.h"
#include "Buff.h"
#include <windows.h>
#include <cstdlib>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

bool collisionTestPaddleBall(Paddle& paddle, Ball& ball)
{
    if (!isIntersecting1(paddle, ball))
        return false;

    ball.update(paddle);
    return true;
}

bool collisionTestBlockBall(Block& block, Ball& ball, vector<Buff>& buffs)
{
    if (!isIntersecting1(block, ball))
        return false;

    float overlapLeft{ ball.right() - block.left() };
    float overlapRight{ block.right() - ball.left() };
    float overlapTop{ ball.bottom() - block.top() };
    float overlapBottom{ block.bottom() - ball.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
    {
        ballFromLeft ? ball.moveLeft() : ball.moveRight();
    }
    else
    {
        ballFromTop ? ball.moveUp() : ball.moveDown();
    }

    Vector2f blockPosition = block.getPosition();
    block.destroy();

    if (rand() % 4 == 0) // 25% szans na spawnienie buffa
    {
        BuffType type = static_cast<BuffType>(rand() % static_cast<int>(BuffType::ScoreMultiplier) + 1); // Losowanie typu buffa
        std::cout << static_cast<int>(type) << std::endl;
        buffs.emplace_back(blockPosition.x, blockPosition.y, type); // Dodanie buffa do wektora
    }

    return true;
}

bool collisionTestBuffPaddle(Buff& buff, Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier)
{
    if (!isIntersecting1(buff, paddle))
        return false;

    buff.activate(paddle, ball, reverseControls, paddleSpeedMultiplier, scoreMultiplier);
    return true;
}

bool isGameOver1(Ball& ball)
{
    return ball.bottom() >= 850;
}

int Poziom1::Start()
{
    Ball ball(550, 425);
    Paddle paddle(400, 790);
    RenderWindow window(VideoMode(1100, 850), "Arcanoid - Poziom 1");

    window.setFramerateLimit(80);
    Event event;
    unsigned blocksX{ 8 }, blocksY{ 6 }, blockWidth{ 70 }, blockHeight{ 30 };
    vector<Block> blocks;
    vector<Buff> buffs;
    int numberOfBlocks = blocksX * blocksY;
    bool reverseControls = false;
    float paddleSpeedMultiplier = 1.0f;
    float scoreMultiplier = 1.0f;

    for (unsigned i = 0; i < blocksY; i++)
    {
        for (unsigned j = 0; j < blocksX; j++)
        {
            blocks.emplace_back((j + 1) * (blockWidth + 50), (i + 1) * (blockHeight + 25), blockWidth, blockHeight);
        }
    }

    Texture Poziom1;
    Poziom1.loadFromFile("Textury/level1.png");

    Sprite sprite1;
    sprite1.setTexture(Poziom1);

    RectangleShape tloPrzegrana;
    tloPrzegrana.setSize(Vector2f(1100, 850));
    Texture mainPrzegrana;
    mainPrzegrana.loadFromFile("Textury/przegrana.png");
    tloPrzegrana.setTexture(&mainPrzegrana);

    RectangleShape tloWygrana;
    tloWygrana.setSize(Vector2f(1100, 850));
    Texture mainWygrana;
    mainWygrana.loadFromFile("Textury/wygrana.png");
    tloWygrana.setTexture(&mainWygrana);

    SoundBuffer buffer;
    buffer.loadFromFile("Audio/level1Audio.wav");
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    while (window.isOpen())
    {
        window.clear();
        window.draw(sprite1);
        window.pollEvent(event);

        if (event.type == Event::Closed)
        {
            window.close();
            break;
        }

        paddle.update();
        ball.update(paddle);

        if (isGameOver1(ball))
        {
            sound.stop();
            window.close();
            RenderWindow Super(VideoMode(1100, 850), "Przegrana");
            SoundBuffer bufferL;
            bufferL.loadFromFile("Audio/koniecAudio.wav");
            Sound soundL;
            soundL.setBuffer(bufferL);
            soundL.setPlayingOffset(sf::seconds(10.f));
            soundL.play();
            while (Super.isOpen())
            {
                Event aevent;
                while (Super.pollEvent(aevent))
                {
                    if (aevent.type == Event::Closed)
                    {
                        Super.close();
                    }
                    if (aevent.type == Event::KeyPressed)
                    {
                        if (aevent.key.code == Keyboard::Escape)
                        {
                            Super.close();
                        }
                    }
                }
                Super.clear();
                Super.draw(tloPrzegrana);
                Super.display();
            }
            return -1;
        }

        if (collisionTestPaddleBall(paddle, ball))
        {
            // Kolizja z paletką
        }

        for (auto& block : blocks)
        {
            if (collisionTestBlockBall(block, ball, buffs))
            {
                numberOfBlocks--;
                break;
            }
        }

        auto iterator = remove_if(begin(blocks), end(blocks), [](Block& block) { return block.isDestroyed(); });
        blocks.erase(iterator, end(blocks));

        if (numberOfBlocks == 0)
        {
            sound.stop();
            window.close();
            return 2;
        }

        for (auto it = buffs.begin(); it != buffs.end();)
        {
            it->fall();
            window.draw(*it);

            if (collisionTestBuffPaddle(*it, paddle, ball, reverseControls, paddleSpeedMultiplier, scoreMultiplier))
            {
                it = buffs.erase(it); // Usuń buff po aktywacji
            }
            else
            {
                ++it;
            }
        }

        buffs.erase(remove_if(buffs.begin(), buffs.end(), [](Buff& buff) {
            buff.updateEffect();
            return buff.top() > 850;
            }), buffs.end());

        for (auto it = buffs.begin(); it != buffs.end();)
        {
            if (it->isEffectEnded())
            {
                it->resetEffect(paddle, ball, reverseControls, paddleSpeedMultiplier, scoreMultiplier);
                it = buffs.erase(it);
            }
            else
            {
                ++it;
            }
        }

        paddle.setVelocity(paddle.getVelocity() * paddleSpeedMultiplier);

        window.draw(ball);
        window.draw(paddle);

        for (auto& block : blocks)
        {
            window.draw(block);
        }

        window.display();
    }
    return 0;
}
