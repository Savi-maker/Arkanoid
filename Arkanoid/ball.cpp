/// @file Ball.cpp
/// @brief Plik zawiera implementacjê klasy Ball, która reprezentuje pi³kê w grze.

#include "Ball.h"
#include "Poziom1.h" // Dodaj ten include
#include <cmath> // Dodaj ten include dla funkcji std::sin i std::cos

/**
 * @brief Konstruktor klasy Ball.
 * @param t_X Pozycja X pi³ki.
 * @param t_Y Pozycja Y pi³ki.
 */
Ball::Ball(float t_X, float t_Y)
    : velocity{ ballVelocity, -ballVelocity } // Ustawienie pocz¹tkowej prêdkoœci
{
    shape.setPosition(t_X, t_Y);
    shape.setRadius(this->ballRadius);
    shape.setFillColor(Color::White);
    shape.setOrigin(this->ballRadius, this->ballRadius);
}

/**
 * @brief Aktualizuje stan pi³ki.
 */
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

/**
 * @brief Aktualizuje stan pi³ki z uwzglêdnieniem paletki.
 * @param paddle Referencja do obiektu Paddle.
 */
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

/**
 * @brief Ustawia prêdkoœæ pi³ki w górê.
 */
void Ball::moveUp()
{
    velocity.y = -ballVelocity;
}

/**
 * @brief Ustawia prêdkoœæ pi³ki w górê i w lewo.
 */
void Ball::moveUpLeft()
{
    velocity.y = -ballVelocity;
    velocity.x = -ballVelocity;
}

/**
 * @brief Ustawia prêdkoœæ pi³ki w górê i w prawo.
 */
void Ball::moveUpRight()
{
    velocity.y = -ballVelocity;
    velocity.x = ballVelocity;
}

/**
 * @brief Ustawia prêdkoœæ pi³ki w dó³.
 */
void Ball::moveDown()
{
    velocity.y = ballVelocity;
}

/**
 * @brief Ustawia prêdkoœæ pi³ki w dó³ i w lewo.
 */
void Ball::moveDownLeft()
{
    velocity.y = ballVelocity;
    velocity.x = -ballVelocity;
}

/**
 * @brief Ustawia prêdkoœæ pi³ki w dó³ i w prawo.
 */
void Ball::moveDownRight()
{
    velocity.y = ballVelocity;
    velocity.x = ballVelocity;
}

/**
 * @brief Ustawia prêdkoœæ pi³ki w prawo.
 */
void Ball::moveRight()
{
    velocity.x = ballVelocity;
}

/**
 * @brief Ustawia prêdkoœæ pi³ki w lewo.
 */
void Ball::moveLeft()
{
    velocity.x = -ballVelocity;
}

/**
 * @brief Zwraca pozycjê pi³ki.
 * @return Pozycja pi³ki.
 */
Vector2f Ball::getPosition() const
{
    return shape.getPosition();
}

/**
 * @brief Zwraca lew¹ pozycjê pi³ki.
 * @return Lewa pozycja pi³ki.
 */
float Ball::left() const
{
    return shape.getPosition().x - shape.getRadius();
}

/**
 * @brief Zwraca praw¹ pozycjê pi³ki.
 * @return Prawa pozycja pi³ki.
 */
float Ball::right() const
{
    return shape.getPosition().x + shape.getRadius();
}

/**
 * @brief Zwraca górn¹ pozycjê pi³ki.
 * @return Górna pozycja pi³ki.
 */
float Ball::top() const
{
    return shape.getPosition().y - shape.getRadius();
}

/**
 * @brief Zwraca doln¹ pozycjê pi³ki.
 * @return Dolna pozycja pi³ki.
 */
float Ball::bottom() const
{
    return shape.getPosition().y + shape.getRadius();
}

/**
 * @brief Zwraca prêdkoœæ pi³ki.
 * @return Prêdkoœæ pi³ki.
 */
Vector2f Ball::getVelocity() const
{
    return velocity;
}

/**
 * @brief Ustawia now¹ prêdkoœæ pi³ki.
 * @param newVelocity Nowa prêdkoœæ pi³ki.
 */
void Ball::setVelocity(const Vector2f& newVelocity)
{
    velocity = newVelocity;
}

/**
 * @brief Zwraca promieñ pi³ki.
 * @return Promieñ pi³ki.
 */
float Ball::getRadius() const
{
    return shape.getRadius();
}

/**
 * @brief Ustawia nowy promieñ pi³ki.
 * @param radius Nowy promieñ pi³ki.
 */
void Ball::setRadius(float radius)
{
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

/**
 * @brief Ustawia stan niewidzialnoœci pi³ki.
 * @param invisible Czy pi³ka ma byæ niewidzialna.
 */
void Ball::setInvisible(bool invisible)
{
    this->invisible = invisible;
    shape.setFillColor(invisible ? Color::Transparent : Color::Red);
    if (invisible) {
        invisibilityClock.restart(); // Restartuj zegar, gdy pi³ka staje siê niewidzialna
    }
}

/**
 * @brief Aktualizuje stan niewidzialnoœci pi³ki.
 */
void Ball::updateInvisibility()
{
    if (invisible && invisibilityClock.getElapsedTime().asSeconds() >= invisibilityDuration)
    {
        invisible = false;
    }
}

/**
 * @brief Rysuje pi³kê na ekranie.
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
 * @brief Sprawdza kolizjê pi³ki z paletk¹.
 * @param paddle Referencja do obiektu Paddle.
 */
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
