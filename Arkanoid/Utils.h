// Utils.h
#pragma once

template <class T1, class T2>
bool isIntersecting(T1& A, T2& B)
{
    return A.right() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom();
}

template <class T1, class T2>
bool isIntersecting(T1& A, T2& B, float offsetX, float offsetY)
{
    return A.right() + offsetX >= B.left() && A.left() + offsetX <= B.right() && A.bottom() + offsetY >= B.top() && A.top() + offsetY <= B.bottom();
}
