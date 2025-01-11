/// @file MainMenu.h
/// @brief Plik nag��wkowy zawieraj�cy deklaracj� klasy MainMenu.

/**
 * @brief Plik nag��wkowy zawieraj�cy klasy, konstruktory, destruktory, definicje oraz dyrektywy.
 */
#pragma once       
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/// @def Max_main_menu
/// @brief Definicja maksymalnego rozmiaru menu jako 5.
#define Max_main_menu 5

/**
 * @brief Klasa reprezentuj�ca menu g��wne.
 */
class MainMenu
{
public:
    /**
     * @brief Konstruktor klasy MainMenu.
     * @param width Szeroko�� okna.
     * @param height Wysoko�� okna.
     */
    MainMenu(float width, float height);

    /**
     * @brief Rysuje menu na ekranie.
     * @param window Okno renderowania.
     */
    void draw(RenderWindow& window);

    /**
     * @brief Przesuwa zaznaczenie w menu w g�r�.
     */
    void MoveUp();

    /**
     * @brief Przesuwa zaznaczenie w menu w d�.
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
    Font font; ///< Czcionka u�ywana w menu
    Text mainMenu[Max_main_menu]; ///< Tablica opcji menu
}
;