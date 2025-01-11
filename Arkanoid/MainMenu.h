/// @file MainMenu.h
/// @brief Plik nag³ówkowy zawieraj¹cy deklaracjê klasy MainMenu.

/**
 * @brief Plik nag³ówkowy zawieraj¹cy klasy, konstruktory, destruktory, definicje oraz dyrektywy.
 */
#pragma once       
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/// @def Max_main_menu
/// @brief Definicja maksymalnego rozmiaru menu jako 5.
#define Max_main_menu 5

/**
 * @brief Klasa reprezentuj¹ca menu g³ówne.
 */
class MainMenu
{
public:
    /**
     * @brief Konstruktor klasy MainMenu.
     * @param width Szerokoœæ okna.
     * @param height Wysokoœæ okna.
     */
    MainMenu(float width, float height);

    /**
     * @brief Rysuje menu na ekranie.
     * @param window Okno renderowania.
     */
    void draw(RenderWindow& window);

    /**
     * @brief Przesuwa zaznaczenie w menu w górê.
     */
    void MoveUp();

    /**
     * @brief Przesuwa zaznaczenie w menu w dó³.
     */
    void MoveDown();

    /**
     * @brief Zwraca indeks wybranej opcji menu.
     * @return Indeks wybranej opcji menu.
     */
    int MainMenuPressed()
    {
        return MainMenuSelected;
    }

    /**
     * @brief Destruktor klasy MainMenu.
     */
    ~MainMenu();

private:
    int MainMenuSelected; ///< Indeks wybranej opcji menu
    Font font; ///< Czcionka u¿ywana w menu
    Text mainMenu[Max_main_menu]; ///< Tablica opcji menu
}
;