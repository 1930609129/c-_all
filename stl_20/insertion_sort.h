//
// Created by xu on 2022/2/24.
//

#ifndef STL_20_INSERTION_SORT_H
#define STL_20_INSERTION_SORT_H


template<typename RandomAccessIterator, typename Compare>
void insertion_sort(RandomAccessIterator first,
                    RandomAccessIterator last,
                    Compare comp);
#include "insertion_sort.cpp"


#endif //STL_20_INSERTION_SORT_H
