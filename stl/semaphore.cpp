//
// Created by xu on 2022/2/21.
//

#include "semaphore.h"

semaphore::semaphore(int i):n_(i)
{

}
void semaphore::acquire()
{
    std::unique_lock<std::mutex> lock(m_);
    cond_.wait(lock,[this]{return n_>0;});
    --n_;
}
void semaphore::release()
{
    std::unique_lock<std::mutex> lock(m_);
    ++n_;
    cond_.notify_one();
}
