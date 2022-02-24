//
// Created by xu on 2022/2/22.
//

#include "memblock.h"

template<typename T,int N> void memblock<T,N>::setmem(int x, T value) {
    memblock[x] = value;
}

template<typename T,int N>T memblock<T,N>::getmem(int x) {
    return memblock[x];
}