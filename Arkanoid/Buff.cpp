// Buff.cpp
/**
 * @file Buff.cpp
 * @brief Plik zawiera implementacjê klasy Buff, która reprezentuje ró¿ne rodzaje buffów w grze.
 */

#include "Buff.h"
#include <iostream>
#include <thread>

 /**
  * @brief Konstruktor klasy Buff.
  * @param t_X Pozycja X buffa.
  * @param t_Y Pozycja Y buffa.
  * @param type Typ buffa.
  */
Buff::Buff(float t_X, float t_Y, BuffType type)
    : type(type)
{
    shape.setPosition(t_X, t_Y);
    shape.setSize(sf::Vector2f(20.0f, 20.0f));
    shape.setFillColor(sf::Color::Green);

    progressBar.setSize(sf::Vector2f(20.0f, 3.0f));
    progressBar.setFillColor(sf::Color::Red);
    progressBar.setPosition(t_X, t_Y - 5.0f);

    std::cout << "Buff created at position: (" << t_X << ", " << t_Y << ")" << std::endl;
}

/**
 * @brief Konstruktor kopiuj¹cy klasy Buff.
 * @param other Obiekt klasy Buff, z którego kopiowane s¹ dane.
 */
Buff::Buff(const Buff& other)
    : shape(other.shape), progressBar(other.progressBar), type(other.type), fallSpeed(other.fallSpeed), effectClock(other.effectClock), effectDuration(other.effectDuration), effectActive(other.effectActive), effectEnded(other.effectEnded)
{
}

/**
 * @brief Operator przypisania dla klasy Buff.
 * @param other Obiekt klasy Buff, z którego kopiowane s¹ dane.
 * @return Referencja do bie¿¹cego obiektu Buff.
 */
Buff& Buff::operator=(const Buff& other)
{
    if (this == &other)
        return *this;

    shape = other.shape;
    progressBar = other.progressBar;
    type = other.type;
    fallSpeed = other.fallSpeed;
    effectClock = other.effectClock;
    effectDuration = other.effectDuration;
    effectActive = other.effectActive;
    effectEnded = other.effectEnded;

    return *this;
}

/**
 * @brief Aktualizuje stan buffa.
 */
void Buff::update()
{
    if (effectActive)
    {
        updateEffect();
    }
}

/**
 * @brief Zwraca typ buffa.
 * @return Typ buffa.
 */
BuffType Buff::getType() const
{
    return type;
}

/**
 * @brief Zwraca lew¹ pozycjê buffa.
 * @return Lewa pozycja buffa.
 */
float Buff::left() const
{
    return shape.getPosition().x;
}

/**
 * @brief Zwraca praw¹ pozycjê buffa.
 * @return Prawa pozycja buffa.
 */
float Buff::right() const
{
    return shape.getPosition().x + shape.getSize().x;
}

/**
 * @brief Zwraca górn¹ pozycjê buffa.
 * @return Górna pozycja buffa.
 */
float Buff::top() const
{
    return shape.getPosition().y;
}

/**
 * @brief Zwraca doln¹ pozycjê buffa.
 * @return Dolna pozycja buffa.
 */
float Buff::bottom() const
{
    return shape.getPosition().y + shape.getSize().y;
}

/**
 * @brief Powoduje opadanie buffa.
 */
void Buff::fall()
{
    shape.move(0, fallSpeed);
    progressBar.move(0, fallSpeed);
}

/**
 * @brief Sprawdza, czy efekt buffa jest aktywny.
 * @return True, jeœli efekt buffa jest aktywny, w przeciwnym razie false.
 */
bool Buff::isEffectActive() const
{
    return effectActive;
}

/**
 * @brief Sprawdza, czy efekt buffa siê zakoñczy³.
 * @return True, jeœli efekt buffa siê zakoñczy³, w przeciwnym razie false.
 */
bool Buff::isEffectEnded() const
{
    return effectEnded;
}

/**
 * @brief Aktywuje efekt buffa.
 * @param paddle Referencja do obiektu Paddle.
 * @param ball Referencja do obiektu Ball.
 * @param reverseControls Referencja do flagi odwróconych sterowañ.
 * @param paddleSpeedMultiplier Referencja do mno¿nika prêdkoœci paletki.
 * @param scoreMultiplier Referencja do mno¿nika punktów.
 */
void Buff::activate(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier)
{
    if (!effectActive)
    {
        effectActive = true;
        effectEnded = false;
        effectClock.restart();
        std::cout << "Buff effect activated: ";

        switch (type)
        {
        case BuffType::SpeedUp:
            std::cout << "SpeedUp" << std::endl;
            ball.setVelocity(ball.getVelocity() * 1.5f);
            break;
        case BuffType::SpeedDown:
            std::cout << "SpeedDown" << std::endl;
            ball.setVelocity(ball.getVelocity() * 0.5f);
            break;
        case BuffType::SizeUp:
            std::cout << "SizeUp" << std::endl;
            paddle.setSize(sf::Vector2f(paddle.getWidth() * 1.5f, paddle.getHeight()));
            break;
        case BuffType::SizeDown:
            std::cout << "SizeDown" << std::endl;
            paddle.setSize(sf::Vector2f(paddle.getWidth() * 0.5f, paddle.getHeight()));
            break;
        case BuffType::ReverseControls:
            std::cout << "ReverseControls" << std::endl;
            reverseControls = true;
            paddle.setReverseControls(reverseControls);
            break;
        case BuffType::BallSpeedUp:
            std::cout << "BallSpeedUp" << std::endl;
            ball.setVelocity(ball.getVelocity() * 1.5f);
            break;
        case BuffType::BallSpeedDown:
            std::cout << "BallSpeedDown" << std::endl;
            ball.setVelocity(ball.getVelocity() * 0.5f);
            break;
        case BuffType::PaddleSpeedUp:
            std::cout << "PaddleSpeedUp" << std::endl;
            paddleSpeedMultiplier = 1.5f;
            break;
        case BuffType::PaddleSpeedDown:
            std::cout << "PaddleSpeedDown" << std::endl;
            paddleSpeedMultiplier = 0.5f;
            break;
        case BuffType::ScoreMultiplier:
            std::cout << "ScoreMultiplier" << std::endl;
            scoreMultiplier = 2.0f;
            break;
        default:
            break;
        }

        std::thread(&Buff::waitForThreeSeconds, this, std::ref(paddle), std::ref(ball), std::ref(reverseControls), std::ref(paddleSpeedMultiplier), std::ref(scoreMultiplier)).detach();
    }
}

/**
 * @brief Czeka trzy sekundy, a nastêpnie resetuje efekt buffa.
 * @param paddle Referencja do obiektu Paddle.
 * @param ball Referencja do obiektu Ball.
 * @param reverseControls Referencja do flagi odwróconych sterowañ.
 * @param paddleSpeedMultiplier Referencja do mno¿nika prêdkoœci paletki.
 * @param scoreMultiplier Referencja do mno¿nika punktów.
 */
void Buff::waitForThreeSeconds(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    resetEffect(paddle, ball, reverseControls, paddleSpeedMultiplier, scoreMultiplier);
}

/**
 * @brief Dezaktywuje efekt buffa.
 */
void Buff::deactivate()
{
    effectActive = false;
    effectEnded = true;
    std::cout << "Buff effect deactivated" << std::endl;
}

/**
 * @brief Aktualizuje efekt buffa.
 */
void Buff::updateEffect()
{
    if (effectActive && effectClock.getElapsedTime().asSeconds() >= effectDuration)
    {
        deactivate();
    }
}

/**
 * @brief Resetuje efekt buffa.
 * @param paddle Referencja do obiektu Paddle.
 * @param ball Referencja do obiektu Ball.
 * @param reverseControls Referencja do flagi odwróconych sterowañ.
 * @param paddleSpeedMultiplier Referencja do mno¿nika prêdkoœci paletki.
 * @param scoreMultiplier Referencja do mno¿nika punktów.
 */
void Buff::resetEffect(Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier)
{
    switch (type)
    {
    case BuffType::SpeedUp:
    case BuffType::SpeedDown:
        ball.setVelocity(sf::Vector2f(5.0f, 5.0f));
        break;
    case BuffType::SizeUp:
    case BuffType::SizeDown:
        paddle.setSize(sf::Vector2f(100.0f, 20.0f));
        break;
    case BuffType::ReverseControls:
        reverseControls = false;
        paddle.setReverseControls(reverseControls);
        break;
    case BuffType::BallSpeedUp:
    case BuffType::BallSpeedDown:
        ball.setVelocity(sf::Vector2f(5.0f, 5.0f));
        break;
    case BuffType::PaddleSpeedUp:
    case BuffType::PaddleSpeedDown:
        paddleSpeedMultiplier = 1.0f;
        break;
    case BuffType::ScoreMultiplier:
        scoreMultiplier = 1.0f;
        break;
    default:
        break;
    }

    effectActive = false;
    effectEnded = true;
    std::cout << "Buff effect reset" << std::endl;
}

/**
 * @brief Rysuje buffa na ekranie.
 * @param target Obiekt docelowy renderowania.
 * @param state Stan renderowania.
 */
void Buff::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
    if (effectActive)
    {
        target.draw(this->progressBar, state);
    }
}
