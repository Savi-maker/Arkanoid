// Buff.h
/// @file Buff.h
/// @brief Plik nag��wkowy zawieraj�cy deklaracj� klasy Buff oraz typ wyliczeniowy BuffType.

#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

/**
 * @brief Typ wyliczeniowy reprezentuj�cy r�ne rodzaje buff�w.
 */
enum class BuffType {
    SpeedUp,
    SpeedDown,
    SizeUp,
    SizeDown,
    ReverseControls,
    BallSpeedUp,
    BallSpeedDown,
    PaddleSpeedUp,
    PaddleSpeedDown,
    ScoreMultiplier
};

/**
 * @brief Klasa reprezentuj�ca buff w grze.
 */
class Buff : public sf::Drawable {
public:
    /**
     * @brief Konstruktor klasy Buff.
     * @param t_X Pozycja X buffa.
     * @param t_Y Pozycja Y buffa.
     * @param type Typ buffa.
     */
    Buff(float t_X, float t_Y, BuffType type);

    /**
     * @brief Konstruktor kopiuj�cy klasy Buff.
     * @param other Inny obiekt klasy Buff.
     */
    Buff(const Buff& other);

    /**
     * @brief Operator przypisania dla klasy Buff.
     * @param other Inny obiekt klasy Buff.
     * @return Referencja do bie��cego obiektu.
     */
    Buff& operator=(const Buff& other);

    /**
     * @brief Aktualizuje stan buffa.
     */
    void update();

    /**
     * @brief Zwraca typ buffa.
     * @return Typ buffa.
     */
    BuffType getType() const;

    /**
     * @brief Zwraca lew� pozycj� buffa.
     * @return Lewa pozycja buffa.
     */
    float left() const;

    /**
     * @brief Zwraca praw� pozycj� buffa.
     * @return Prawa pozycja buffa.
     */
    float right() const;

    /**
     * @brief Zwraca g�rn� pozycj� buffa.
     * @return G�rna pozycja buffa.
     */
    float top() const;

    /**
     * @brief Zwraca doln� pozycj� buffa.
     * @return Dolna pozycja buffa.
     */
    float bottom() const;

    /**
     * @brief Powoduje opadanie buffa.
     */
    void fall();

    /**
     * @brief Aktywuje efekt buffa.
     * @param paddle Referencja do obiektu Paddle.
     * @param ball Referencja do obiektu Ball.
     * @param reverseControls Flaga odwr�cenia sterowania.
     * @param paddleSpeedMultiplier Mno�nik pr�dko�ci paletki.
     * @param scoreMultiplier Mno�nik punkt�w.
     */
    void activate(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier);

    /**
     * @brief Dezaktywuje efekt buffa.
     */
    void deactivate();

    /**
     * @brief Sprawdza, czy efekt buffa jest aktywny.
     * @return true, je�li efekt jest aktywny; w przeciwnym razie false.
     */
    bool isEffectActive() const;

    /**
     * @brief Sprawdza, czy efekt buffa si� zako�czy�.
     * @return true, je�li efekt si� zako�czy�; w przeciwnym razie false.
     */
    bool isEffectEnded() const;

    /**
     * @brief Resetuje efekt buffa.
     * @param paddle Referencja do obiektu Paddle.
     * @param ball Referencja do obiektu Ball.
     * @param reverseControls Flaga odwr�cenia sterowania.
     * @param paddleSpeedMultiplier Mno�nik pr�dko�ci paletki.
     * @param scoreMultiplier Mno�nik punkt�w.
     */
    void resetEffect(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier);

    /**
     * @brief Aktualizuje efekt buffa.
     */
    void updateEffect();

    /**
     * @brief Rysuje buff na ekranie.
     * @param target Obiekt docelowy renderowania.
     * @param state Stan renderowania.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

private:
    /**
     * @brief Oczekuje trzy sekundy przed aktywacj� efektu buffa.
     * @param paddle Referencja do obiektu Paddle.
     * @param ball Referencja do obiektu Ball.
     * @param reverseControls Flaga odwr�cenia sterowania.
     * @param paddleSpeedMultiplier Mno�nik pr�dko�ci paletki.
     * @param scoreMultiplier Mno�nik punkt�w.
     */
    void waitForThreeSeconds(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier);

    sf::RectangleShape shape; ///< Kszta�t buffa
    sf::RectangleShape progressBar; ///< Pasek post�pu efektu buffa
    BuffType type; ///< Typ buffa
    float fallSpeed{ 1.0f }; ///< Pr�dko�� opadania buffa
    sf::Clock effectClock; ///< Zegar efektu buffa
    float effectDuration{ 3.0f }; ///< Czas trwania efektu buffa
    bool effectActive{ false }; ///< Flaga aktywno�ci efektu buffa
    bool effectEnded{ false }; ///< Flaga zako�czenia efektu buffa
}

;