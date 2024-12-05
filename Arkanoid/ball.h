#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp> // Dodaj ten include
#include "Paddle.h"
using namespace sf;

class Ball : public Drawable
{
public:
    Ball(float t_X, float t_Y);
    Ball() = delete;
    ~Ball() = default;
    void update();
    void update(const Paddle& paddle);
    void moveUp();
    void moveUpLeft();
    void moveUpRight();
    void moveDown();
    void moveDownLeft();
    void moveDownRight();
    void moveRight();
    void moveLeft();
    Vector2f getPosition() const;
    float left() const;
    float right() const;
    float top() const;
    float bottom() const;
    Vector2f getVelocity() const;
    void setVelocity(const Vector2f& newVelocity);
    float getRadius() const;
    void setRadius(float radius);
    void setInvisible(bool invisible);
    void draw(RenderTarget& target, RenderStates state) const override;
    void checkCollisionWithPaddle(const Paddle& paddle);
    sf::Clock invisibilityClock; // Dodaj zegar do śledzenia czasu niewidzialności
    float invisibilityDuration{ 1.0f }; // Czas trwania niewidzialności w sekundach
    void updateInvisibility(); // Deklaracja metody do aktualizacji stanu niewidzialności

private:
    CircleShape shape;
    const float ballRadius{ 10.0f };
    float ballVelocity{ 5.0f };
    Vector2f velocity;
    bool invisible{ false }; // Flaga niewidzialności
};

