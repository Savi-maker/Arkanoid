#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * @brief Klasa reprezentuj�ca blok w grze.
 */
class Block : public Drawable
{
public:
    /**
     * @brief Konstruktor klasy Block.
     * @param t_X Pozycja X bloku.
     * @param t_Y Pozycja Y bloku.
     * @param t_Width Szeroko�� bloku.
     * @param t_Height Wysoko�� bloku.
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
     * @brief Zwraca pozycj� bloku.
     * @return Pozycja bloku.
     */
    Vector2f getPosition();

    /**
     * @brief Zwraca lew� pozycj� bloku.
     * @return Lewa pozycja bloku.
     */
    float left();

    /**
     * @brief Zwraca praw� pozycj� bloku.
     * @return Prawa pozycja bloku.
     */
    float right();

    /**
     * @brief Zwraca g�rn� pozycj� bloku.
     * @return G�rna pozycja bloku.
     */
    float top();

    /**
     * @brief Zwraca doln� pozycj� bloku.
     * @return Dolna pozycja bloku.
     */
    float bottom();

    /**
     * @brief Sprawdza, czy blok jest zniszczony.
     * @return true, je�li blok jest zniszczony; w przeciwnym razie false.
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
     * @brief Zwraca kszta�t bloku.
     * @return Referencja do kszta�tu bloku.
     */
    RectangleShape& getShape();

private:
    RectangleShape shape; ///< Kszta�t bloku
    bool destroyed{ false }; ///< Flaga zniszczenia bloku
}
;