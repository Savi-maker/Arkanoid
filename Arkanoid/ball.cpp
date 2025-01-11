/// @file Ball.cpp
/// @brief Plik zawiera implementacj� klasy Ball, kt�ra reprezentuje pi�k� w grze.

#include "Ball.h"
#include "Poziom1.h" // Dodaj ten include
#include <cmath> // Dodaj ten include dla funkcji std::sin i std::cos

/**
 * @brief Konstruktor klasy Ball.
 * @param t_X Pozycja X pi�ki.
 * @param t_Y Pozycja Y pi�ki.
 */
Ball::Ball(float t_X, float t_Y)
    : velocity{ ballVelocity, -ballVelocity } // Ustawienie pocz�tkowej pr�dko�ci
{
    shape.setPosition(t_X, t_Y);
    shape.setRadius(this->ballRadius);
    shape.setFillColor(Color::White);
    shape.setOrigin(this->ballRadius, this->ballRadius);
}

/**
 * @brief Aktualizuje stan pi�ki.
 */
void Ball::update()
{
    updateInvisibility(); // Aktualizacja stanu niewidzialno�ci

    shape.move(this->velocity);

    // Kolizja z lew� i praw� �cian�
    if (left() < 0)
    {
        velocity.x = ballVelocity;
    }
    else if (right() > 1100)
    {
        velocity.x = -ballVelocity;
    }

    // Kolizja z g�rn� �cian�
    if (top() < 0)
    {
        velocity.y = ballVelocity;
    }
}

/**
 * @brief Aktualizuje stan pi�ki z uwzgl�dnieniem paletki.
 * @param paddle Referencja do obiektu Paddle.
 */
void Ball::update(const Paddle& paddle)
{
    updateInvisibility(); // Aktualizacja stanu niewidzialno�ci

    shape.move(this->velocity);

    if (isIntersecting1(*this, paddle))
    {
        checkCollisionWithPaddle(paddle);
    }

    // Kolizja z lew� i praw� �cian�
    if (left() < 0)
    {
        velocity.x = ballVelocity;
    }
    else if (right() > 1100)
    {
        velocity.x = -ballVelocity;
    }

    // Kolizja z g�rn� �cian�
    if (top() < 0)
    {
        velocity.y = ballVelocity;
    }
}

/**
 * @brief Ustawia pr�dko�� pi�ki w g�r�.
 */
void Ball::moveUp()
{
    velocity.y = -ballVelocity;
}

/**
 * @brief Ustawia pr�dko�� pi�ki w g�r� i w lewo.
 */
void Ball::moveUpLeft()
{
    velocity.y = -ballVelocity;
    velocity.x = -ballVelocity;
}

/**
 * @brief Ustawia pr�dko�� pi�ki w g�r� i w prawo.
 */
void Ball::moveUpRight()
{
    velocity.y = -ballVelocity;
    velocity.x = ballVelocity;
}

/**
 * @brief Ustawia pr�dko�� pi�ki w d�.
 */
void Ball::moveDown()
{
    velocity.y = ballVelocity;
}

/**
 * @brief Ustawia pr�dko�� pi�ki w d� i w lewo.
 */
void Ball::moveDownLeft()
{
    velocity.y = ballVelocity;
    velocity.x = -ballVelocity;
}

/**
 * @brief Ustawia pr�dko�� pi�ki w d� i w prawo.
 */
void Ball::moveDownRight()
{
    velocity.y = ballVelocity;
    velocity.x = ballVelocity;
}

/**
 * @brief Ustawia pr�dko�� pi�ki w prawo.
 */
void Ball::moveRight()
{
    velocity.x = ballVelocity;
}

/**
 * @brief Ustawia pr�dko�� pi�ki w lewo.
 */
void Ball::moveLeft()
{
    velocity.x = -ballVelocity;
}

/**
 * @brief Zwraca pozycj� pi�ki.
 * @return Pozycja pi�ki.
 */
Vector2f Ball::getPosition() const
{
    return shape.getPosition();
}

/**
 * @brief Zwraca lew� pozycj� pi�ki.
 * @return Lewa pozycja pi�ki.
 */
float Ball::left() const
{
    return shape.getPosition().x - shape.getRadius();
}

/**
 * @brief Zwraca praw� pozycj� pi�ki.
 * @return Prawa pozycja pi�ki.
 */
float Ball::right() const
{
    return shape.getPosition().x + shape.getRadius();
}

/**
 * @brief Zwraca g�rn� pozycj� pi�ki.
 * @return G�rna pozycja pi�ki.
 */
float Ball::top() const
{
    return shape.getPosition().y - shape.getRadius();
}

/**
 * @brief Zwraca doln� pozycj� pi�ki.
 * @return Dolna pozycja pi�ki.
 */
float Ball::bottom() const
{
    return shape.getPosition().y + shape.getRadius();
}

/**
 * @brief Zwraca pr�dko�� pi�ki.
 * @return Pr�dko�� pi�ki.
 */
Vector2f Ball::getVelocity() const
{
    return velocity;
}

/**
 * @brief Ustawia now� pr�dko�� pi�ki.
 * @param newVelocity Nowa pr�dko�� pi�ki.
 */
void Ball::setVelocity(const Vector2f& newVelocity)
{
    velocity = newVelocity;
}

/**
 * @brief Zwraca promie� pi�ki.
 * @return Promie� pi�ki.
 */
float Ball::getRadius() const
{
    return shape.getRadius();
}

/**
 * @brief Ustawia nowy promie� pi�ki.
 * @param radius Nowy promie� pi�ki.
 */
void Ball::setRadius(float radius)
{
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

/**
 * @brief Ustawia stan niewidzialno�ci pi�ki.
 * @param invisible Czy pi�ka ma by� niewidzialna.
 */
void Ball::setInvisible(bool invisible)
{
    this->invisible = invisible;
    shape.setFillColor(invisible ? Color::Transparent : Color::Red);
    if (invisible) {
        invisibilityClock.restart(); // Restartuj zegar, gdy pi�ka staje si� niewidzialna
    }
}

/**
 * @brief Aktualizuje stan niewidzialno�ci pi�ki.
 */
void Ball::updateInvisibility()
{
    if (invisible && invisibilityClock.getElapsedTime().asSeconds() >= invisibilityDuration)
    {
        invisible = false;
    }
}

/**
 * @brief Rysuje pi�k� na ekranie.
 * @param target Obiekt docelowy renderowania.
 * @param state Stan renderowania.
 */
void Ball::draw(RenderTarget& target, RenderStates state) const
{
    if (!invisible)
    {
        target.draw(this->shape, state);
    }
}

/**
 * @brief Sprawdza kolizj� pi�ki z paletk�.
 * @param paddle Referencja do obiektu Paddle.
 */
void Ball::checkCollisionWithPaddle(const Paddle& paddle)
{
    // Sprawdzenie, z kt�rej strony nast�pi�a kolizja
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

    // Odbicie pi�ki od paletki
    velocity.y = -ballVelocity;

    // Zmiana k�ta odbicia w zale�no�ci od miejsca uderzenia w paletk�
    float paddleCenter = paddle.getPosition().x;
    float ballCenter = getPosition().x;
    float distanceFromCenter = ballCenter - paddleCenter;
    float percentageDistance = distanceFromCenter / (paddle.getWidth() / 2.0f);

    // Obliczenie k�ta odbicia w zakresie od 15 do 165 stopni
    float angle = 15 + (percentageDistance * 75);
    float radians = angle * (3.14159f / 180.0f);

    // Ustawienie nowej pr�dko�ci pi�ki
    velocity.x = ballVelocity * std::sin(radians);
    velocity.y = -ballVelocity * std::cos(radians);
}
