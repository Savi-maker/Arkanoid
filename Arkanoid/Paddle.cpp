#include "Paddle.h"

Paddle::Paddle(float t_X, float t_Y)
{
    shape.setPosition(t_X, t_Y);
    shape.setSize({ this->paddleWidth, this->paddleHeight });
    shape.setFillColor(Color::Green);
    shape.setOrigin(this->paddleWidth / 2.f, this->paddleHeight / 2.f);
}

Paddle::~Paddle()
{
}

void Paddle::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(this->shape, state);
}

void Paddle::update()
{
    shape.move(this->velocity);

    if (reverseControls)
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->right() < 1100)
        {
            velocity.x = paddleVelocity;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->left() > 0)
        {
            velocity.x = -paddleVelocity;
        }
        else
        {
            velocity.x = 0;
        }
    }
    else
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 0)
        {
            velocity.x = -paddleVelocity;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < 1100)
        {
            velocity.x = paddleVelocity;
        }
        else
        {
            velocity.x = 0;
        }
    }
}

void Paddle::moveLeft()
{
    velocity.x = -paddleVelocity;
}

void Paddle::moveRight()
{
    velocity.x = paddleVelocity;
}

void Paddle::setReverseControls(bool reverse)
{
    reverseControls = reverse;
}

float Paddle::left() const
{
    return this->shape.getPosition().x - shape.getSize().x / 2.f;
}

float Paddle::right() const
{
    return this->shape.getPosition().x + shape.getSize().x / 2.f;
}

float Paddle::top() const
{
    return this->shape.getPosition().y - shape.getSize().y / 2.f;
}

float Paddle::bottom() const
{
    return this->shape.getPosition().y + shape.getSize().y / 2.f;
}

Vector2f Paddle::getPosition() const
{
    return shape.getPosition();
}

Vector2f Paddle::getVelocity() const
{
    return velocity;
}

float Paddle::getWidth() const
{
    return shape.getSize().x;
}

float Paddle::getHeight() const
{
    return shape.getSize().y;
}

void Paddle::setSize(const Vector2f& size)
{
    shape.setSize(size);
}

void Paddle::setVelocity(const Vector2f& newVelocity)
{
    velocity = newVelocity;
}

