#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp> // Dodaj ten include
#include "Paddle.h"
using namespace sf;

/**
 * @brief Klasa reprezentująca piłkę w grze.
 */
class Ball : public Drawable
{
public:
    /**
     * @brief Konstruktor klasy Ball.
     * @param t_X Pozycja X piłki.
     * @param t_Y Pozycja Y piłki.
     */
    Ball(float t_X, float t_Y);

    /**
     * @brief Usunięty konstruktor domyślny.
     */
    Ball() = delete;

    /**
     * @brief Domyślny destruktor klasy Ball.
     */
    ~Ball() = default;

    /**
     * @brief Aktualizuje stan piłki.
     */
    void update();

    /**
     * @brief Aktualizuje stan piłki w zależności od pozycji paletki.
     * @param paddle Referencja do obiektu Paddle.
     */
    void update(const Paddle& paddle);

    /**
     * @brief Przesuwa piłkę w górę.
     */
    void moveUp();

    /**
     * @brief Przesuwa piłkę w górę i w lewo.
     */
    void moveUpLeft();

    /**
     * @brief Przesuwa piłkę w górę i w prawo.
     */
    void moveUpRight();

    /**
     * @brief Przesuwa piłkę w dół.
     */
    void moveDown();

    /**
     * @brief Przesuwa piłkę w dół i w lewo.
     */
    void moveDownLeft();

    /**
     * @brief Przesuwa piłkę w dół i w prawo.
     */
    void moveDownRight();

    /**
     * @brief Przesuwa piłkę w prawo.
     */
    void moveRight();

    /**
     * @brief Przesuwa piłkę w lewo.
     */
    void moveLeft();

    /**
     * @brief Zwraca pozycję piłki.
     * @return Pozycja piłki.
     */
    Vector2f getPosition() const;

    /**
     * @brief Zwraca lewą pozycję piłki.
     * @return Lewa pozycja piłki.
     */
    float left() const;

    /**
     * @brief Zwraca prawą pozycję piłki.
     * @return Prawa pozycja piłki.
     */
    float right() const;

    /**
     * @brief Zwraca górną pozycję piłki.
     * @return Górna pozycja piłki.
     */
    float top() const;

    /**
     * @brief Zwraca dolną pozycję piłki.
     * @return Dolna pozycja piłki.
     */
    float bottom() const;

    /**
     * @brief Zwraca prędkość piłki.
     * @return Prędkość piłki.
     */
    Vector2f getVelocity() const;

    /**
     * @brief Ustawia nową prędkość piłki.
     * @param newVelocity Nowa prędkość piłki.
     */
    void setVelocity(const Vector2f& newVelocity);

    /**
     * @brief Zwraca promień piłki.
     * @return Promień piłki.
     */
    float getRadius() const;

    /**
     * @brief Ustawia nowy promień piłki.
     * @param radius Nowy promień piłki.
     */
    void setRadius(float radius);

    /**
     * @brief Ustawia stan niewidzialności piłki.
     * @param invisible Flaga niewidzialności.
     */
    void setInvisible(bool invisible);

    /**
     * @brief Rysuje piłkę na ekranie.
     * @param target Obiekt docelowy renderowania.
     * @param state Stan renderowania.
     */
    void draw(RenderTarget& target, RenderStates state) const override;

    /**
     * @brief Sprawdza kolizję piłki z paletką.
     * @param paddle Referencja do obiektu Paddle.
     */
    void checkCollisionWithPaddle(const Paddle& paddle);

    sf::Clock invisibilityClock; ///< Zegar do śledzenia czasu niewidzialności
    float invisibilityDuration{ 1.0f }; ///< Czas trwania niewidzialności w sekundach

    /**
     * @brief Aktualizuje stan niewidzialności piłki.
     */
    void updateInvisibility();

private:
    CircleShape shape; ///< Kształt piłki
    const float ballRadius{ 10.0f }; ///< Promień piłki
    float ballVelocity{ 5.0f }; ///< Prędkość piłki
    Vector2f velocity; ///< Wektor prędkości piłki
    bool invisible{ false }; ///< Flaga niewidzialności
}
;