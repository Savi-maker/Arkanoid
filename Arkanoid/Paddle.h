/// @file Paddle.h
/// @brief Plik nag³ówkowy zawieraj¹cy deklaracjê klasy Paddle.

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * @brief Klasa reprezentuj¹ca paletkê w grze.
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
     * @brief Przesuwa paletkê w lewo.
     */
    void moveLeft();

    /**
     * @brief Przesuwa paletkê w prawo.
     */
    void moveRight();

    /**
     * @brief Ustawia odwrócone sterowanie paletk¹.
     * @param reverse Czy sterowanie ma byæ odwrócone.
     */
    void setReverseControls(bool reverse); // Deklaracja metody setReverseControls

    /**
     * @brief Zwraca lew¹ pozycjê paletki.
     * @return Lewa pozycja paletki.
     */
    float left() const;

    /**
     * @brief Zwraca praw¹ pozycjê paletki.
     * @return Prawa pozycja paletki.
     */
    float right() const;

    /**
     * @brief Zwraca górn¹ pozycjê paletki.
     * @return Górna pozycja paletki.
     */
    float top() const;

    /**
     * @brief Zwraca doln¹ pozycjê paletki.
     * @return Dolna pozycja paletki.
     */
    float bottom() const;

    /**
     * @brief Zwraca pozycjê paletki.
     * @return Pozycja paletki.
     */
    Vector2f getPosition() const;

    /**
     * @brief Zwraca prêdkoœæ paletki.
     * @return Prêdkoœæ paletki.
     */
    Vector2f getVelocity() const;

    /**
     * @brief Zwraca szerokoœæ paletki.
     * @return Szerokoœæ paletki.
     */
    float getWidth() const;

    /**
     * @brief Zwraca wysokoœæ paletki.
     * @return Wysokoœæ paletki.
     */
    float getHeight() const;

    /**
     * @brief Ustawia nowy rozmiar paletki.
     * @param size Nowy rozmiar paletki.
     */
    void setSize(const Vector2f& size); // Setter for shape size

    /**
     * @brief Ustawia now¹ prêdkoœæ paletki.
     * @param newVelocity Nowa prêdkoœæ paletki.
     */
    void setVelocity(const Vector2f& newVelocity); // Setter for velocity

    /**
     * @brief Rysuje paletkê na ekranie.
     * @param target Obiekt docelowy renderowania.
     * @param state Stan renderowania.
     */
    void draw(RenderTarget& target, RenderStates state) const override;

private:
    RectangleShape shape; ///< Kszta³t paletki
    Texture paddleTexture; ///< Tekstura paletki
    const float paddleWidth{ 80.0f }; ///< Szerokoœæ paletki
    const float paddleHeight{ 20.0f }; ///< Wysokoœæ paletki
    const float paddleVelocity{ 8.0f }; ///< Prêdkoœæ paletki
    Vector2f velocity{ paddleVelocity, 0.f }; ///< Prêdkoœæ paletki
    bool reverseControls{ false }; ///< Flaga odwracania sterowania
}

;