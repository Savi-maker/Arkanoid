#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Ball.h"
#include "Paddle.h"
using namespace sf;

enum class BuffType
{
    SpeedUp,
    SpeedDown,
    SizeUp,
    SizeDown,
    ReverseControls,
    BallSpeedUp,
    BallSpeedDown,
    ScreenShake,
    InvisibleBall,
    DoubleBall,
    BallSizeUp,
    BallSizeDown,
    PaddleSpeedUp,
    PaddleSpeedDown,
    ExtraLife,
    ScoreMultiplier,
    Count
};

class Buff : public Drawable
{
public:
    Buff(float t_X, float t_Y, BuffType type);
    ~Buff() = default;
    Buff(const Buff& other);
    Buff& operator=(const Buff& other);
    void update();
    BuffType getType() const;
    float left() const;
    float right() const;
    float top() const;
    float bottom() const;
    void fall();
    void activate();
    void deactivate();
    void waitForThreeSeconds();
    bool isEffectActive() const;
    bool isEffectEnded() const;
    void resetEffect(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier);
    inline float getEffectDuration() const;
    inline const sf::Clock& getEffectClock() const;
    void updateEffect();

private:
    RectangleShape shape;
    RectangleShape progressBar;
    BuffType type;
    float fallSpeed{ 1.0f };
    sf::Clock effectClock;
    float effectDuration{ 3.0f };
    bool effectActive{ false };
    bool effectEnded{ false };
    void draw(RenderTarget& target, RenderStates state) const override;
};

inline float Buff::getEffectDuration() const
{
    return effectDuration;
}

inline const sf::Clock& Buff::getEffectClock() const
{
    return effectClock;
}


