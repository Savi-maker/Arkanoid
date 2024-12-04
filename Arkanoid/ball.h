#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
using namespace sf;

/// Ball
/**
 * Implementacja klasy z odwolaniem do klasy skladowej jezyka sfml ktora zawiera
 * Funkcja tworzaca konstruktor z dwoma parameatrami
 * Funkcja usuwajaca dowolny konstruktor
 * Funkcja dodjaca dowolny destruktor
 * Funkcja aktualizujaca polozenie pileczki
 * Funkcja wektorowa
 * Utworzenie okregu funkcji sfml
 * Implementacja promienia pileczki
 * Implementacja predkosci pileczki
 * Funkcja wektorowa ustalajaca szybkosc pileczki na planszy
 *
*/
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
    float getRadius() const; // Getter for radius
    void setRadius(float radius); // Setter for radius
    void setInvisible(bool invisible); // Setter for invisibility
    void draw(RenderTarget& target, RenderStates state) const override;
    void checkCollisionWithPaddle(const Paddle& paddle);

private:
    CircleShape shape;
    const float ballRadius{ 10.0f };
    float ballVelocity{ 5.0f };
    Vector2f velocity;
    bool invisible{ false }; // Flaga niewidzialności
};

