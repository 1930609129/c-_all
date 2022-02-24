//
// Created by xu on 2022/2/24.
//

#ifndef STL_20_TIME_SORT_H
#define STL_20_TIME_SORT_H

#endif //STL_20_TIME_SORT_H

#include <vector>
#include <functional>
#include <string>
#include <chrono>
#include <iostream>
#include <cassert>

template<typename T, template<typename ...>typename Container = std::vector,typename Compare = std::less<T>>
static void time_sort(const std::string &sort_name,Container<T> data,
                      void(*sort_fun)
                      (typename Container<T>::iterator,typename Container<T>::iterator,Compare) = std::sort,
        Compare comp = std::less<T>())
{
    auto start = std::chrono::high_resolution_clock::now();
    (*sort_fun)(data.begin(),data.end(),comp);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    assert(std::is_sorted(data.begin(),data.end()));
    std::cout << sort_name << " results for size = " << data.size() << " = " << duration.count() <<" microseconds" << std::endl;
}