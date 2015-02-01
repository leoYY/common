/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file thread/condition.h
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/01 13:26:15
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef PS_SPI_THREAD/CONDITION_H
#define PS_SPI_THREAD/CONDITION_H

#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include "thread/mutex.h"
#include "util/noncopyable.h"

namespace common {
namespace thread {

class Condition: public common::util::noncopyable {
public:
    explicit Condtiion(Mutex& mutex): _mutex(mutex) {
        pthread_cond_init(&_cond, _mutex.PthreadMutex(), NULL);
    }

    ~Condition() {
        pthread_cond_destroy(&_cond);
    }

    void Wait() {
        pthread_cond_wait(&_cond, _mutex.PthreadMutex()); 
    }

    bool WaitForTime(unsigned long ms) {
        struct timespec now; 
        clock_gettime(CLOCK_REALTIME, &now);
        
        now.tv_sec += ms / 1000;
        now.tv_nsec += (ms % 1000) * 1000000;

        if (now.tv_nsec >= 1000000000) {
            now.tv_sec += 1; 
            now.tv_nsec -= 1000000000;
        }

        return ETIMEDOUT == 
            pthread_cond_timedwait(
                    &_cond, 
                    _mutex.PthreadMutex(),
                    &now);
    }
    
    void Signal() {
        pthread_cond_signal(&_cond);
    }

    void SignalAll() {
        pthread_cond_broadcast(&_cond); 
    }
private:
    pthread_cond_t _cond;
    Mutex& _mutex;
};

}   // ending namespace thread
}   // ending namespace common

#endif  //PS_SPI_THREAD/CONDITION_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
