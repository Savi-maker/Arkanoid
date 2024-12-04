///Poziom1
/**
 * Plik naglowkowy zawierajacy klasy
*/
#pragma once
#include <SFML/Graphics.hpp>
#include "Buff.h" // Dodano nag³ówek Buff

using namespace std;
using namespace sf;

///Poziom1
/**
 * Klasa zawiera
 * Funkcja inicjalizuje funkcje start
 * Destruktor
*/
template <class T1, class T2> bool isIntersecting1(T1& A, T2& B)
{
		return A.right() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom();

}

class Poziom1
{
public:
	int Start();

	~Poziom1();

private:
	vector<Buff> buffs; // Wektor buffów
};





