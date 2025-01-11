#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * @brief Klasa reprezentuj¹ca blok w grze.
 */
class Block : public Drawable
{
public:
    /**
     * @brief Konstruktor klasy Block.
     * @param t_X Pozycja X bloku.
     * @param t_Y Pozycja Y bloku.
     * @param t_Width Szerokoœæ bloku.
     * @param t_Height Wysokoœæ bloku.
     */
    Block(float t_X, float t_Y, float t_Width, float t_Height);

    /**
     * @brief Destruktor klasy Block.
     */
    ~Block();

    /**
     * @brief Aktualizuje stan bloku.
     */
    void update();

    /**
     * @brief Zwraca pozycjê bloku.
     * @return Pozycja bloku.
     */
    Vector2f getPosition();

    /**
     * @brief Zwraca lew¹ pozycjê bloku.
     * @return Lewa pozycja bloku.
     */
    float left();

    /**
     * @brief Zwraca praw¹ pozycjê bloku.
     * @return Prawa pozycja bloku.
     */
    float right();

    /**
     * @brief Zwraca górn¹ pozycjê bloku.
     * @return Górna pozycja bloku.
     */
    float top();

    /**
     * @brief Zwraca doln¹ pozycjê bloku.
     * @return Dolna pozycja bloku.
     */
    float bottom();

    /**
     * @brief Sprawdza, czy blok jest zniszczony.
     * @return true, jeœli blok jest zniszczony; w przeciwnym razie false.
     */
    bool isDestroyed();

    /**
     * @brief Niszczy blok.
     */
    void destroy();

    /**
     * @brief Zwraca rozmiar bloku.
     * @return Rozmiar bloku.
     */
    Vector2f getSize();

    /**
     * @brief Rysuje blok na ekranie.
     * @param target Obiekt docelowy renderowania.
     * @param states Stan renderowania.
     */
    virtual void draw(RenderTarget& target, RenderStates states) const override;

    /**
     * @brief Zwraca kszta³t bloku.
     * @return Referencja do kszta³tu bloku.
     */
    RectangleShape& getShape();

private:
    RectangleShape shape; ///< Kszta³t bloku
    bool destroyed{ false }; ///< Flaga zniszczenia bloku
}
;