//
// Created by xu on 2022/2/24.
//

template<typename RandomAccessIterator, typename Compare>
void insertion_sort(RandomAccessIterator first,
                    RandomAccessIterator last,
                    Compare comp)
{
    for(auto sorted = last-1;sorted != first;--sorted)
    {
        auto next = sorted - 1;
        int value = *next;
        for(auto itr=sorted;itr!=last;++itr,++next)
        {
            if(comp(value,*itr))
                break;
            *next = *itr;
        }
        *next = value;
    }
}