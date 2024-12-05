#include "Ball.h"
#include "Poziom1.h" // Dodaj ten include
#include <cmath> // Dodaj ten include dla funkcji std::sin i std::cos

Ball::Ball(float t_X, float t_Y)
    : velocity{ ballVelocity, -ballVelocity } // Ustawienie pocz¹tkowej prêdkoœci
{
    shape.setPosition(t_X, t_Y);
    shape.setRadius(this->ballRadius);
    shape.setFillColor(Color::White);
    shape.setOrigin(this->ballRadius, this->ballRadius);
}

void Ball::update()
{
    updateInvisibility(); // Aktualizacja stanu niewidzialnoœci

    shape.move(this->velocity);

    // Kolizja z lew¹ i praw¹ œcian¹
    if (left() < 0)
    {
        velocity.x = ballVelocity;
    }
    else if (right() > 1100)
    {
        velocity.x = -ballVelocity;
    }

    // Kolizja z górn¹ œcian¹
    if (top() < 0)
    {
        velocity.y = ballVelocity;
    }
}

void Ball::update(const Paddle& paddle)
{
    updateInvisibility(); // Aktualizacja stanu niewidzialnoœci

    shape.move(this->velocity);

    if (isIntersecting1(*this, paddle))
    {
        checkCollisionWithPaddle(paddle);
    }

    // Kolizja z lew¹ i praw¹ œcian¹
    if (left() < 0)
    {
        velocity.x = ballVelocity;
    }
    else if (right() > 1100)
    {
        velocity.x = -ballVelocity;
    }

    // Kolizja z górn¹ œcian¹
    if (top() < 0)
    {
        velocity.y = ballVelocity;
    }
}

void Ball::moveUp()
{
    velocity.y = -ballVelocity;
}

void Ball::moveUpLeft()
{
    velocity.y = -ballVelocity;
    velocity.x = -ballVelocity;
}

void Ball::moveUpRight()
{
    velocity.y = -ballVelocity;
    velocity.x = ballVelocity;
}

void Ball::moveDown()
{
    velocity.y = ballVelocity;
}

void Ball::moveDownLeft()
{
    velocity.y = ballVelocity;
    velocity.x = -ballVelocity;
}

void Ball::moveDownRight()
{
    velocity.y = ballVelocity;
    velocity.x = ballVelocity;
}

void Ball::moveRight()
{
    velocity.x = ballVelocity;
}

void Ball::moveLeft()
{
    velocity.x = -ballVelocity;
}

Vector2f Ball::getPosition() const
{
    return shape.getPosition();
}

float Ball::left() const
{
    return shape.getPosition().x - shape.getRadius();
}

float Ball::right() const
{
    return shape.getPosition().x + shape.getRadius();
}

float Ball::top() const
{
    return shape.getPosition().y - shape.getRadius();
}

float Ball::bottom() const
{
    return shape.getPosition().y + shape.getRadius();
}

Vector2f Ball::getVelocity() const
{
    return velocity;
}

void Ball::setVelocity(const Vector2f& newVelocity)
{
    velocity = newVelocity;
}

float Ball::getRadius() const
{
    return shape.getRadius();
}

void Ball::setRadius(float radius)
{
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

void Ball::setInvisible(bool invisible)
{
    this->invisible = invisible;
    shape.setFillColor(invisible ? Color::Transparent : Color::Red);
    if (invisible) {
        invisibilityClock.restart(); // Restartuj zegar, gdy pi³ka staje siê niewidzialna
    }
}

void Ball::updateInvisibility()
{
    if (invisible && invisibilityClock.getElapsedTime().asSeconds() >= invisibilityDuration)
    {
        invisible = false;
    }
}


void Ball::draw(RenderTarget& target, RenderStates state) const
{
    if (!invisible)
    {
        target.draw(this->shape, state);
    }
}

void Ball::checkCollisionWithPaddle(const Paddle& paddle)
{
    // Sprawdzenie, z której strony nast¹pi³a kolizja
    float overlapLeft{ right() - paddle.left() };
    float overlapRight{ paddle.right() - left() };
    float overlapTop{ bottom() - paddle.top() };
    float overlapBottom{ paddle.bottom() - top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
    {
        ballFromLeft ? moveLeft() : moveRight();
    }
    else
    {
        ballFromTop ? moveUp() : moveDown();
    }

    // Odbicie pi³ki od paletki
    velocity.y = -ballVelocity;

    // Zmiana k¹ta odbicia w zale¿noœci od miejsca uderzenia w paletkê
    float paddleCenter = paddle.getPosition().x;
    float ballCenter = getPosition().x;
    float distanceFromCenter = ballCenter - paddleCenter;
    float percentageDistance = distanceFromCenter / (paddle.getWidth() / 2.0f);

    // Obliczenie k¹ta odbicia w zakresie od 15 do 165 stopni
    float angle = 15 + (percentageDistance * 75);
    float radians = angle * (3.14159f / 180.0f);

    // Ustawienie nowej prêdkoœci pi³ki
    velocity.x = ballVelocity * std::sin(radians);
    velocity.y = -ballVelocity * std::cos(radians);
}

