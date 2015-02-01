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
#ifndef PS_SPI_THREAD/MUTEX_H
#define PS_SPI_THREAD/MUTEX_H

#include <pthread.h>
#include "util/noncopyable.h"

namespace common {
namespace thread {

class Mutex : public common::util::noncopyable {
public:
    Mutex()  {
        pthread_mutex_init(&_mutex, NULL);
    }

    ~Mutex() {
        pthread_mutex_destroy(&_mutex); 
    }
    
    void Lock() {
        pthread_mutex_lock(&_mutex); 
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
    MutexScoped() {}
    Mutex& _mutex;
};


}   // ending namespace thread
}   // ending namespace common
#endif  //PS_SPI_THREAD/MUTEX_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
