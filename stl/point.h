//
// Created by xu on 2022/2/23.
//

#ifndef STL_POINT_H
#define STL_POINT_H

#include <utility>

template<typename T1,typename T2>
class point {
public:
    point(T1 x,T2 y);

    T1 &x;
    T2 &y;

private:
    std::pair<T1,T2> pair_;
};


#endif //STL_POINT_H
