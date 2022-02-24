//
// Created by xu on 2022/2/22.
//

#ifndef STL_CONTAINER_H
#define STL_CONTAINER_H

template <typename T>
class container {
public:
    explicit container (const T &arg);
    T increase ();

private:
    T element;
};


#endif //STL_CONTAINER_H
