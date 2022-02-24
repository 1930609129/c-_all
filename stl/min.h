//
// Created by xu on 2022/2/22.
//

#ifndef STL_MIN_H
#define STL_MIN_H
#include <type_traits>

template <typename T>
T min(T p1,T p2)
{
    return p1<p2 ? p1:p2;
}

template <typename T>
T min(T p1,T p2,T p3)
{
    return min(p1,p2)<p3? min(p1,p2):p3;
}

template <typename A,typename B>
auto min_ex(A a,B b)->typename std::remove_reference<decltype(a<b?a:b)>::type
{
//    decltype ( 表达式 )
    return a<b ? a : b;
}

#endif //STL_MIN_H
