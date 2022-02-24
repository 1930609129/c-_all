//
// Created by xu on 2022/2/23.
//

#include "point.h"
template <typename T1,typename T2>
point<T1,T2>::point (T1 x, T2 y):pair_(MOVE(x),MOVE(y)),x(pair_.first),y(pair_.second) {

}