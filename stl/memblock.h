//
// Created by xu on 2022/2/22.
//

#ifndef STL_MEMBLOCK_H
#define STL_MEMBLOCK_H

template<typename T,int N>
class memblock {
public:
    void setmem(int x,T value);
    T getmem(int x);

private:
    T memblock[N] = {0};
};

#endif //STL_MEMBLOCK_H
