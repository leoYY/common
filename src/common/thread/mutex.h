/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file thread/mutex.h
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/01 13:20:00
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef _THREAD_MUTEX_H
#define _THREAD_MUTEX_H

#include <pthread.h>
#include <errno.h>
#include <assert.h>
#include "common/util/noncopyable.h"
#include "common/util/log.h"

namespace common {
namespace thread {

class Mutex : public common::util::noncopyable {
public:
    Mutex()  {
        int ret = pthread_mutex_init(&_mutex, NULL);
        if (ret != 0) {
            FATAL_LOG(
                    "%d pthread mutex init failed errno[%d] [%s]\n", 
                    pthread_self(), 
                    errno, 
                    strerror(errno));     
            assert(ret == 0);
        }
    }

    ~Mutex() {
        if (0 != pthread_mutex_destroy(&_mutex)) {
            FATAL_LOG(
                    "%d pthread mutex destroy failed errno[%d] [%s]\n", 
                    pthread_self(), 
                    errno, 
                    strerror(errno)); 
        }

    }
    
    void Lock() {
#ifdef UTTEST
        {
            common::util::TimerDebuger timer(
                    "thread [%x] mutex [%p] costs ", 
                    pthread_self(), 
                    &_mutex);
#endif
        pthread_mutex_lock(&_mutex); 
#ifdef UTTEST
        }
#endif 
    }

    void UnLock() {
        pthread_mutex_unlock(&_mutex); 
    }

    pthread_mutex_t* PthreadMutex() {
        return &_mutex; 
    }
private:
    pthread_mutex_t _mutex;
};

class MutexScoped : public common::util::noncopyable {
public:
    explicit MutexScoped(Mutex& mutex): _mutex(mutex) {
        _mutex.Lock();     
    }

    ~MutexScoped() {
        _mutex.UnLock(); 
    }
private:
    Mutex& _mutex;
};


}   // ending namespace thread
}   // ending namespace common
#endif  //PS_SPI_THREAD/MUTEX_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
