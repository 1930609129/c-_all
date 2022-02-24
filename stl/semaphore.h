//
// Created by xu on 2022/2/21.
//

#ifndef STL_SEMAPHORE_H
#define STL_SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class semaphore
{
public:
    explicit semaphore(int i);
    void acquire();
    void release();
private:
    std::mutex m_;
    std::condition_variable cond_;
    int n_;
};

#endif //STL_SEMAPHORE_H
