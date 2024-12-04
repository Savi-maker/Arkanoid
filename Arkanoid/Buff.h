#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

enum class BuffType
{
    SpeedUp,
    SpeedDown,
    SizeUp,
    SizeDown,
    ReverseControls,
    BallSpeedUp,
    PaddleSpeedUp,
    ScreenShake,
    InvisibleBall,
    DoubleBall,
    BallSizeUp,
    BallSizeDown,
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

    Buff(const Buff& other); // Deklaracja konstruktora kopiuj¹cego
    Buff& operator=(const Buff& other); // Deklaracja operatora przypisania

    void update();
    bool isActive() const;
    BuffType getType() const;

    float left() const;
    float right() const;
    float top() const;
    float bottom() const;

private:
    CircleShape shape;
    BuffType type;
    bool active;
    Clock clock;
    const float duration{ 3.0f }; // Czas trwania buffa w sekundach

    void draw(RenderTarget& target, RenderStates state) const override;
};


