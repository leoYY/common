/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file src/common/event/event.h
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/16 22:03:47
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef _EVENT_EVENT_H
#define _EVENT_EVENT_H

#include "common/util/noncopyable.h"
#include "common/util/closure.h"

namespace common {
namespace event {

class EventPool : public common::util::noncopyable{
public:
    explicit EventPool(int work_num) :
        _timer_id(0),
        _stop(false),
        _work_num(work_num) {}

    ~EventPool() {}

    bool Start();

    // fd event
    int AddReadableEvent(int fd, Closure*);
    int AddWriteableEvent(int fd, Closure*);
    void DelReadableEvent(int fd);
    void DelWriteableEvent(int fd);

    // time event
    int AddTimeEvent(Closure*, unsigned long ms);
    void DelTimeEvent(int timer_id);
private:
    volatile int timer_id;
    volatile bool _stop;        
    int _work_num;
};

}   // ending namespace event
}   // ending namespace common

#endif  //_EVENT/EVENT_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
