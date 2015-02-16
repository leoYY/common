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
#ifndef _THREAD_CONDITION_H
#define _THREAD_CONDITION_H

#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include "common/thread/mutex.h"
#include "common/util/noncopyable.h"
#include "common/util/time_debuger.h"

namespace common {
namespace thread {

class Condition: public common::util::noncopyable {
public:
    explicit Condition(Mutex& mutex): _mutex(mutex) {
        if (0 != pthread_cond_init(&_cond, NULL)) {
            FATAL_LOG(
                    "condition[%p] init failed err[%d] [%s]", 
                    &_cond, 
                    errno, 
                    strerror(errno)); 
            abort();
        }
    }

    ~Condition() {
        if (0 != pthread_cond_destroy(&_cond)) {
            FATAL_LOG(
                    "condition[%p] destroy failed err[%d] [%s]", 
                    &_cond,
                    errno,
                    strerror(errno)); 
        }
    }

    void Wait() {
#ifdef UTTEST
        common::util::TimerDebuger timer(
                "thread[%x] condition[%p] at mutex[%p] wait costs ",
                pthread_self(),
                &_cond,
                _mutex.PthreadMutex()); 
#endif
        int err = pthread_cond_wait(&_cond, _mutex.PthreadMutex()); 
        if (err != 0) {
            WARNING_LOG(
                    "thread [%x] condition[%p] wait failed err[%d] [%s]",
                    pthread_self(),
                    &_cond,
                    errno,
                    strerror(errno));
            // condition wait failed may not any matter, user will check conditon value
        }
    }

    bool WaitForTime(unsigned long ms) {
#ifdef UTTEST
        common::util::TimerDebuger timer(
                "thread[%x] condition[%p] at mutex[%p] wait costs ",
                pthread_self(),
                &_cond,
                _mutex.PthreadMutex());
#endif
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
        int err = pthread_cond_signal(&_cond);
        if (err != 0) {
            //@NOTE how to trigger signal failed? 
            FATAL_LOG(
                    "thread[%x] condition[%p] signal failed err[%d] [%s]",
                    pthread_self(),
                    &_cond,
                    errno,
                    strerror(errno));
        }
    }

    void SignalAll() {
        int err = pthread_cond_broadcast(&_cond); 
        if (err != 0) {
            //@NOTE how to trigger signal failed? 
            FATAL_LOG(
                    "thread[%x] condition[%p] signal failed err[%d] [%s]",
                    pthread_self(),
                    &_cond,
                    errno,
                    strerror(errno));
        }
    }
private:
    pthread_cond_t _cond;
    Mutex& _mutex;
};

}   // ending namespace thread
}   // ending namespace common

#endif  //PS_SPI_THREAD/CONDITION_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
