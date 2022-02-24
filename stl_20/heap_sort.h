//
// Created by xu on 2022/2/24.
//

#ifndef STL_20_HEAP_SORT_H
#define STL_20_HEAP_SORT_H

#include <algorithm>

template<typename RandomAccessIterator, typename Compare>
void heap_sort(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
{
    std::make_heap(first,last,comp);
    std::sort_heap(first,last,comp);
}

#endif //STL_20_HEAP_SORT_H
