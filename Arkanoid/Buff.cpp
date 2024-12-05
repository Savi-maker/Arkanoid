#include "Buff.h"
#include <iostream>
#include "ball.h"

Buff::Buff(float t_X, float t_Y, BuffType type)
    : type(type)
{
    shape.setPosition(t_X, t_Y);
    shape.setSize(Vector2f(20.0f, 20.0f));
    shape.setFillColor(Color::Green);

    progressBar.setSize(Vector2f(20.0f, 3.0f));
    progressBar.setFillColor(Color::Red);
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

void Buff::activate()
{
    if (!effectActive)
    {
        effectActive = true;
        effectEnded = false;
        effectClock.restart();
        std::cout << "Buff effect activated" << std::endl;

    }
}
void Buff::waitForThreeSeconds()
{
    this->updateEffect();
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
        ball.setVelocity(Vector2f(5.0f, 5.0f));
        break;
    case BuffType::SizeUp:
    case BuffType::SizeDown:
        paddle.setSize(Vector2f(100.0f, 20.0f));
        break;
    case BuffType::ReverseControls:
        reverseControls = false;
        paddle.setReverseControls(reverseControls);
        break;
    case BuffType::BallSpeedUp:
    case BuffType::BallSpeedDown:
        ball.setVelocity(Vector2f(5.0f, 5.0f));
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
    progressBar.setSize(Vector2f(20.0f, 3.0f));
    std::cout << "Buff effect reset" << std::endl;
}

void Buff::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(this->shape, state);
    if (effectActive)
    {
        target.draw(this->progressBar, state);
    }
}
