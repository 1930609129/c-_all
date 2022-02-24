//
// Created by xu on 2022/2/24.
//

#ifndef STL_20_GENERATE_DATA_H
#define STL_20_GENERATE_DATA_H

#include <vector>

template<typename T, template<typename ...>typename Container = std::vector>
static Container<T> generate_data(int size,int biggest)
{
    Container<T> data;
    std::generate_n(std::back_inserter(data),size,[biggest](){return rand()%biggest;});
    return data;
}


#endif //STL_20_GENERATE_DATA_H
