/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file thread/thread_pool.h
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/01 13:50:40
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef _THREAD_THREAD_POOL_H
#define _THREAD_THREAD_POOL_H

#include <sys/time.h>
#include <pthread.h>
#include <vector>
#include <deque>
#include "common/thread/mutex.h"
#include "common/thread/condition.h"
#include "common/util/noncopyable.h"
#include "common/util/closure.h"
#include "common/util/log.h"

namespace common {
namespace thread {

using common::util::Closure;

class ThreadPool: public common::util::noncopyable {
public:
    explicit ThreadPool(int work_num): 
        _mutex(),
        _cond(_mutex),
        _work_num(work_num),
        _pending_tasks(0),
        _pids(),
        _stop(false),
        _task_queue()
    { }

    ~ThreadPool() {
        Stop(false);
    }   

    bool Start();

    void AddTask(Closure* func) {
        MutexScoped lock(_mutex);
        _task_queue.push_back(func);
        _pending_tasks ++;
        TRACE_LOG("%d add task count[%d]\n", pthread_self(), _pending_tasks);
        _cond.Signal();
    }

    void AddPriorityTask(Closure* func) {
        MutexScoped lock(_mutex); 
        _task_queue.push_front(func);
        _pending_tasks ++;
        TRACE_LOG("%d add task count[%d]\n", pthread_self(), _pending_tasks);
        _cond.Signal();
    }
    
    void Stop(bool wait);
private:
    static void* ThreadWrapper(void* args) {
        reinterpret_cast<ThreadPool*>(args)->ThreadProc();
        return NULL;
    }

    void ThreadProc(); 

    Mutex _mutex;
    Condition _cond;
    int _work_num;
    volatile int _pending_tasks;
    std::vector<pthread_t> _pids;
    volatile bool _stop;
    std::deque<Closure*> _task_queue;
};

}   // ending namespace thread
}   // ending namespace common

#endif  //PS_SPI_THREAD/THREAD_POOL_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
