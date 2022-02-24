//
// Created by xu on 2022/2/22.
//

#include "pair.h"

namespace my_pair
{
#if PASS_BY_VALUE == 0
    template<typename T>
    pair<T>::pair(const T &f, const T &s):first(f),second(s) {
//        first = f;
//        second = s;
    }
#else
template<typename T>
pair<T>::pair(T f,T s):first(MOVE(f)),second(MOVE(s))
{

}
#endif

template<typename T> T pair<T>::max() {
    return first < second ? second : first;
}

}
