/// @file Paddle.h
/// @brief Plik nag��wkowy zawieraj�cy deklaracj� klasy Paddle.

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * @brief Klasa reprezentuj�ca paletk� w grze.
 */
class Paddle : public Drawable
{
public:
    /**
     * @brief Konstruktor klasy Paddle.
     * @param t_X Pozycja X paletki.
     * @param t_Y Pozycja Y paletki.
     */
    Paddle(float t_X, float t_Y);

    /**
     * @brief Destruktor klasy Paddle.
     */
    ~Paddle();

    /**
     * @brief Aktualizuje stan paletki.
     */
    void update();

    /**
     * @brief Przesuwa paletk� w lewo.
     */
    void moveLeft();

    /**
     * @brief Przesuwa paletk� w prawo.
     */
    void moveRight();

    /**
     * @brief Ustawia odwr�cone sterowanie paletk�.
     * @param reverse Czy sterowanie ma by� odwr�cone.
     */
    void setReverseControls(bool reverse); // Deklaracja metody setReverseControls

    /**
     * @brief Zwraca lew� pozycj� paletki.
     * @return Lewa pozycja paletki.
     */
    float left() const;

    /**
     * @brief Zwraca praw� pozycj� paletki.
     * @return Prawa pozycja paletki.
     */
    float right() const;

    /**
     * @brief Zwraca g�rn� pozycj� paletki.
     * @return G�rna pozycja paletki.
     */
    float top() const;

    /**
     * @brief Zwraca doln� pozycj� paletki.
     * @return Dolna pozycja paletki.
     */
    float bottom() const;

    /**
     * @brief Zwraca pozycj� paletki.
     * @return Pozycja paletki.
     */
    Vector2f getPosition() const;

    /**
     * @brief Zwraca pr�dko�� paletki.
     * @return Pr�dko�� paletki.
     */
    Vector2f getVelocity() const;

    /**
     * @brief Zwraca szeroko�� paletki.
     * @return Szeroko�� paletki.
     */
    float getWidth() const;

    /**
     * @brief Zwraca wysoko�� paletki.
     * @return Wysoko�� paletki.
     */
    float getHeight() const;

    /**
     * @brief Ustawia nowy rozmiar paletki.
     * @param size Nowy rozmiar paletki.
     */
    void setSize(const Vector2f& size); // Setter for shape size

    /**
     * @brief Ustawia now� pr�dko�� paletki.
     * @param newVelocity Nowa pr�dko�� paletki.
     */
    void setVelocity(const Vector2f& newVelocity); // Setter for velocity

    /**
     * @brief Rysuje paletk� na ekranie.
     * @param target Obiekt docelowy renderowania.
     * @param state Stan renderowania.
     */
    void draw(RenderTarget& target, RenderStates state) const override;

private:
    RectangleShape shape; ///< Kszta�t paletki
    Texture paddleTexture; ///< Tekstura paletki
    const float paddleWidth{ 80.0f }; ///< Szeroko�� paletki
    const float paddleHeight{ 20.0f }; ///< Wysoko�� paletki
    const float paddleVelocity{ 8.0f }; ///< Pr�dko�� paletki
    Vector2f velocity{ paddleVelocity, 0.f }; ///< Pr�dko�� paletki
    bool reverseControls{ false }; ///< Flaga odwracania sterowania
}

;