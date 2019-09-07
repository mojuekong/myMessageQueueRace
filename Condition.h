//
// Created by pengyibo on 2019-08-26.
//

#ifndef QUEUESTORE_CONDITION_H
#define QUEUESTORE_CONDITION_H




#include "MutexLock.h"
#include <pthread.h>
#include <errno.h>

namespace CONCURRENT
{

    class Condition
    {
    public:
        explicit Condition(MutexLock& mutex) : mutex_(mutex)
        {
            pthread_cond_init(&pcond_, NULL);
        }

        ~Condition()
        {
            pthread_cond_destroy(&pcond_);
        }

        void wait()
        {
            pthread_cond_wait(&pcond_, mutex_.getPthreadMutex());
        }

        // returns true if time out, false otherwise.
        bool waitForSeconds(int seconds)
        {
            struct timespec abstime;
            clock_gettime(CLOCK_REALTIME, &abstime);
            abstime.tv_sec += seconds;
            return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.getPthreadMutex(), &abstime);
        }

        void notify()
        {
            pthread_cond_signal(&pcond_);
        }

        void notifyAll()
        {
            pthread_cond_broadcast(&pcond_);
        }

    private:
        MutexLock& mutex_;
        pthread_cond_t pcond_;
    };

}
#endif  // MUDUO_BASE_CONDITION_H


