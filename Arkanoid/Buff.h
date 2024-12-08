// Buff.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

enum class BuffType {
    SpeedUp,
    SpeedDown,
    SizeUp,
    SizeDown,
    ReverseControls,
    BallSpeedUp,
    BallSpeedDown,
    PaddleSpeedUp,
    PaddleSpeedDown,
    ScoreMultiplier
};

class Buff : public sf::Drawable {
public:
    Buff(float t_X, float t_Y, BuffType type);
    Buff(const Buff& other);
    Buff& operator=(const Buff& other);
    void update();
    BuffType getType() const;
    float left() const;
    float right() const;
    float top() const;
    float bottom() const;
    void fall();
    void activate(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier);
    void deactivate();
    bool isEffectActive() const;
    bool isEffectEnded() const;
    void resetEffect(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier);
    void updateEffect();
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

private:
    void waitForThreeSeconds(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier);

    sf::RectangleShape shape;
    sf::RectangleShape progressBar;
    BuffType type;
    float fallSpeed{ 1.0f };
    sf::Clock effectClock;
    float effectDuration{ 3.0f };
    bool effectActive{ false };
    bool effectEnded{ false };
};
