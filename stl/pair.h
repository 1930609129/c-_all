//
// Created by xu on 2022/2/22.
//

#ifndef STL_PAIR_H
#define STL_PAIR_H

namespace my_pair
{
    template<typename T>
    class pair{
    public:
#if PASS_BY_VALUE == 0
        pair(const T &f,const T &s);
#else
        pair(T f,T s);
#endif
        T max();

        T first;
        T second;
    };
}

#endif //STL_PAIR_H
