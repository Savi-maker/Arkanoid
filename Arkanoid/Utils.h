/// @file Utils.h
/// @brief Plik zawiera funkcje pomocnicze do sprawdzania kolizji.

#pragma once

/**
 * @brief Sprawdza, czy dwa obiekty koliduj¹ ze sob¹.
 * @tparam T1 Typ pierwszego obiektu.
 * @tparam T2 Typ drugiego obiektu.
 * @param A Referencja do pierwszego obiektu.
 * @param B Referencja do drugiego obiektu.
 * @return true, jeœli obiekty koliduj¹; w przeciwnym razie false.
 */
template <class T1, class T2>
bool isIntersecting(T1& A, T2& B)
{
    return A.right() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom();
}

/**
 * @brief Sprawdza, czy dwa obiekty koliduj¹ ze sob¹ z uwzglêdnieniem przesuniêcia.
 * @tparam T1 Typ pierwszego obiektu.
 * @tparam T2 Typ drugiego obiektu.
 * @param A Referencja do pierwszego obiektu.
 * @param B Referencja do drugiego obiektu.
 * @param offsetX Przesuniêcie w osi X.
 * @param offsetY Przesuniêcie w osi Y.
 * @return true, jeœli obiekty koliduj¹; w przeciwnym razie false.
 */
template <class T1, class T2>
bool isIntersecting(T1& A, T2& B, float offsetX, float offsetY)
{
    return A.right() + offsetX >= B.left() && A.left() + offsetX <= B.right() && A.bottom() + offsetY >= B.top() && A.top() + offsetY <= B.bottom();
}
