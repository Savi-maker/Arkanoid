/// @file Poziom1.h
/// @brief Plik nag��wkowy zawieraj�cy deklaracje klas i funkcji dla poziomu 1.

#pragma once
#include <SFML/Graphics.hpp>
#include "Buff.h" // Dodano nag��wek Buff

using namespace std;
using namespace sf;

/**
 * @brief Sprawdza, czy dwa obiekty koliduj� ze sob�.
 * @tparam T1 Typ pierwszego obiektu.
 * @tparam T2 Typ drugiego obiektu.
 * @param A Referencja do pierwszego obiektu.
 * @param B Referencja do drugiego obiektu.
 * @return true, je�li obiekty koliduj�; w przeciwnym razie false.
 */
template <class T1, class T2>
bool isIntersecting1(T1& A, T2& B)
{
    return A.right() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom();
}

/**
 * @brief Klasa reprezentuj�ca poziom 1 gry.
 */
class Poziom1
{
public:
    /**
     * @brief Inicjalizuje poziom 1 gry.
     * @return Kod zako�czenia.
     */
    int Start();

    /**
     * @brief Destruktor klasy Poziom1.
     */
    ~Poziom1();

private:
    vector<Buff> buffs; ///< Wektor buff�w
}
;