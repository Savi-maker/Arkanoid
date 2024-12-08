// Buff.cpp
#include "Buff.h"
#include <iostream>
#include <thread>

Buff::Buff(float t_X, float t_Y, BuffType type)
    : type(type)
{
    shape.setPosition(t_X, t_Y);
    shape.setSize(sf::Vector2f(20.0f, 20.0f));
    shape.setFillColor(sf::Color::Green);

    progressBar.setSize(sf::Vector2f(20.0f, 3.0f));
    progressBar.setFillColor(sf::Color::Red);
    progressBar.setPosition(t_X, t_Y - 5.0f);

    std::cout << "Buff created at position: (" << t_X << ", " << t_Y << ")" << std::endl;
}

Buff::Buff(const Buff& other)
    : shape(other.shape), progressBar(other.progressBar), type(other.type), fallSpeed(other.fallSpeed), effectClock(other.effectClock), effectDuration(other.effectDuration), effectActive(other.effectActive), effectEnded(other.effectEnded)
{
}

Buff& Buff::operator=(const Buff& other)
{
    if (this == &other)
        return *this;

    shape = other.shape;
    progressBar = other.progressBar;
    type = other.type;
    fallSpeed = other.fallSpeed;
    effectClock = other.effectClock;
    effectDuration = other.effectDuration;
    effectActive = other.effectActive;
    effectEnded = other.effectEnded;

    return *this;
}

void Buff::update()
{
    if (effectActive)
    {
        updateEffect();
    }
}

BuffType Buff::getType() const
{
    return type;
}

float Buff::left() const
{
    return shape.getPosition().x;
}

float Buff::right() const
{
    return shape.getPosition().x + shape.getSize().x;
}

float Buff::top() const
{
    return shape.getPosition().y;
}

float Buff::bottom() const
{
    return shape.getPosition().y + shape.getSize().y;
}

void Buff::fall()
{
    shape.move(0, fallSpeed);
    progressBar.move(0, fallSpeed);
}

bool Buff::isEffectActive() const
{
    return effectActive;
}

bool Buff::isEffectEnded() const
{
    return effectEnded;
}

void Buff::activate(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier)
{
    if (!effectActive)
    {
        effectActive = true;
        effectEnded = false;
        effectClock.restart();
        std::cout << "Buff effect activated: ";

        switch (type)
        {
        case BuffType::SpeedUp:
            std::cout << "SpeedUp" << std::endl;
            ball.setVelocity(ball.getVelocity() * 1.5f);
            break;
        case BuffType::SpeedDown:
            std::cout << "SpeedDown" << std::endl;
            ball.setVelocity(ball.getVelocity() * 0.5f);
            break;
        case BuffType::SizeUp:
            std::cout << "SizeUp" << std::endl;
            paddle.setSize(sf::Vector2f(paddle.getWidth() * 1.5f, paddle.getHeight()));
            break;
        case BuffType::SizeDown:
            std::cout << "SizeDown" << std::endl;
            paddle.setSize(sf::Vector2f(paddle.getWidth() * 0.5f, paddle.getHeight()));
            break;
        case BuffType::ReverseControls:
            std::cout << "ReverseControls" << std::endl;
            reverseControls = true;
            paddle.setReverseControls(reverseControls);
            break;
        case BuffType::BallSpeedUp:
            std::cout << "BallSpeedUp" << std::endl;
            ball.setVelocity(ball.getVelocity() * 1.5f);
            break;
        case BuffType::BallSpeedDown:
            std::cout << "BallSpeedDown" << std::endl;
            ball.setVelocity(ball.getVelocity() * 0.5f);
            break;
        case BuffType::PaddleSpeedUp:
            std::cout << "PaddleSpeedUp" << std::endl;
            paddleSpeedMultiplier = 1.5f;
            break;
        case BuffType::PaddleSpeedDown:
            std::cout << "PaddleSpeedDown" << std::endl;
            paddleSpeedMultiplier = 0.5f;
            break;
        case BuffType::ScoreMultiplier:
            std::cout << "ScoreMultiplier" << std::endl;
            scoreMultiplier = 2.0f;
            break;
        default:
            break;
        }

        std::thread(&Buff::waitForThreeSeconds, this, std::ref(paddle), std::ref(ball), std::ref(reverseControls), std::ref(paddleSpeedMultiplier), std::ref(scoreMultiplier)).detach();
    }
}

void Buff::waitForThreeSeconds(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    resetEffect(paddle, ball, reverseControls, paddleSpeedMultiplier, scoreMultiplier);
}

void Buff::deactivate()
{
    effectActive = false;
    effectEnded = true;
    std::cout << "Buff effect deactivated" << std::endl;
}

void Buff::updateEffect()
{
    if (effectActive && effectClock.getElapsedTime().asSeconds() >= effectDuration)
    {
        deactivate();
    }
}

void Buff::resetEffect(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier)
{
    switch (type)
    {
    case BuffType::SpeedUp:
    case BuffType::SpeedDown:
        ball.setVelocity(sf::Vector2f(5.0f, 5.0f));
        break;
    case BuffType::SizeUp:
    case BuffType::SizeDown:
        paddle.setSize(sf::Vector2f(100.0f, 20.0f));
        break;
    case BuffType::ReverseControls:
        reverseControls = false;
        paddle.setReverseControls(reverseControls);
        break;
    case BuffType::BallSpeedUp:
    case BuffType::BallSpeedDown:
        ball.setVelocity(sf::Vector2f(5.0f, 5.0f));
        break;
    case BuffType::PaddleSpeedUp:
    case BuffType::PaddleSpeedDown:
        paddleSpeedMultiplier = 1.0f;
        break;
    case BuffType::ScoreMultiplier:
        scoreMultiplier = 1.0f;
        break;
    default:
        break;
    }

    effectActive = false;
    effectEnded = true;
  //  progressBar.setSize(sf::Vector2f(20.0f, 3.0f));
    std::cout << "Buff effect reset" << std::endl;
}

void Buff::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
    if (effectActive)
    {
        target.draw(this->progressBar, state);
    }
}
