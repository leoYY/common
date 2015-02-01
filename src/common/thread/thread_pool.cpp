/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file thread/thread_pool.cpp
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/01 15:00:29
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "thread/thread_pool.h"

namespace common {
namespace thread {

void ThreadPool::ThreadProc() {
    while (true) {
        Closure* callback;
        {
            MutexScoped lock(_mutex); 
            while (_pending_tasks == 0 && !_stop) {
                _cond.Wait();
            }

            if (_stop) {
                break; 
            }
            callback = _task_queue.front();
            _task_queue.pop_front();
            _pending_tasks --;
        } 
        callback->Run();
        callback = NULL;
    }
}

void ThreadPool::Stop(bool wait) {
    if (wait) {
        while (_pending_tasks > 0) {
            usleep(1000); 
        } 
    }

    {
        MutexScoped lock(_mutex); 
        _stop = true;
        _cond.SignalAll();
    }

    std::vector<pthread_t>::iterator it;
    for (it = _pids.begin(); it != _pids.end(); it++) {
        pthread_t& pid = *it;
        pthread_join(pid, NULL); 
    }
    //FIXME when wait is false, Closure should be delete by threadpool?
    while (_pending_tasks != 0) {
        Closure* callback = _task_queue.front(); 
        delete callback;
        _task_queue.pop_front();
        _pending_tasks --;
    }
    return;
}

void ThreadPool::Start() {
    _stop = false;
    for (int i = 0; i < _work_num; i++) {
        pthread_t pid; 
        pthread_create(&pid, NULL, ThreadPool::ThreadWrapper, this);
        _pids.push_back(pid);
    }
    return;
}

}   // ending namespace thread
}   // ending namespace common

/* vim: set ts=4 sw=4 sts=4 tw=100 */
