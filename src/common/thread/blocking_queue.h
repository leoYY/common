/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file blocking_queue.h
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/01 17:12:27
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef PS_SPI_BLOCKING_QUEUE_H
#define PS_SPI_BLOCKING_QUEUE_H

#include <deque>
#include "util/noncopyable.h"
#include "thread/mutex.h"
#include "thread/condition.h"

namespace common {
namespace thread {

template <typename T>
class BlockingQueue : public common::util::noncopyable {
public:
    explicit BlockingQueue(int queue_size): 
        _mutex(),
        _not_full(),
        _not_empty(),
        _queue_size(queue_size),
        _queue() {}

    BlockingQueue():
        _mutex(),
        _not_full(),
        _not_empty(),
        _queue_size(-1),
        _queue() {}

    ~BlockingQueue() {}

    // push not wait for empty
    bool Push(const T& t) {
        MutexScoped lock(_mutex); 
        if (IsFull()) {
            return false;
        }

        _queue.push_back(t);
        _not_empty.Signal();
        return true;
    }

    bool PushForTimed(const T& t, long ms) {
        MutexScoped lock(_mutex); 
        if (IsFull()) {
            if (ms < 0) {
                while (IsFull()) {
                    _not_full.Wait();
                }
            } else {
                // WaitForTime ret true when ETIMEDOUT
                if (_not_full.WaitForTime(static_cast<unsigned long>(ms))) {
                    return false; 
                } 
                if (IsFull()) {
                    return false; 
                }
            }
        }
        
        _queue.push_back(t);
        _not_empty.Signal();
        return true;
    }

    bool Take(T& t) {
        MutexScoped lock(_mutex); 
        if (IsEmpty()) {
            return false; 
        }

        t = _queue.front();
        _queue.pop_front();
        _not_full.Signal();
        return true;
    }

    bool TakeForTimed(T& t, long ms) {
        MutexScoped lock(_mutex);
        if (IsEmpty()) {
            if (ms < 0) {
                while (IsEmpty()) {
                    _not_empty.Wait(); 
                } 
            } else {
                if (_not_empty.WaitForTime(static_cast<unsigned long>(ms))) {
                    return false; 
                }   
                if (IsEmpty()) {
                    return false; 
                }
            }
        }

        t = _queue.front();
        _queue.pop_front();
        _not_full.Signal();
        return true;
    }

private:

    bool IsFull() {
        // NOTE if _queue_size < 0, no limitation for queue size
        if (_queue_size < 0) {
            return false; 
        }
        return _queue.size() == _queue_size; 
    }

    bool IsEmpty() {
        return _queue.size() == 0; 
    }

    Mutex _mutex;
    Condition _not_full;
    condition _not_empty;
    int _queue_size;
    std::deque<T> _queue; 
}
}   // ending namespace thread
}   // ending namespace common

#endif  //PS_SPI_BLOCKING_QUEUE_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
