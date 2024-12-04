#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle : public Drawable
{
public:
    Paddle(float t_X, float t_Y);
    ~Paddle();
    void update();
    void moveLeft();
    void moveRight();
    void setReverseControls(bool reverse); // Deklaracja metody setReverseControls
    float left() const;
    float right() const;
    float top() const;
    float bottom() const;
    Vector2f getPosition() const;
    Vector2f getVelocity() const;
    float getWidth() const;
    float getHeight() const;
    void setSize(const Vector2f& size); // Setter for shape size
    void setVelocity(const Vector2f& newVelocity); // Setter for velocity
    void draw(RenderTarget& target, RenderStates state) const override;

private:
    RectangleShape shape;
    const float paddleWidth{ 80.0f };
    const float paddleHeight{ 20.0f };
    const float paddleVelocity{ 8.0f };
    Vector2f velocity{ paddleVelocity, 0.f };
    bool reverseControls{ false }; // Flaga odwracania sterowania
};

