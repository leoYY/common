/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file src/common/event/event_driver.h
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/17 01:20:49
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef EVENT_EVENT_DRIVER_H
#define EVENT_EVENT_DRIVER_H

namespace common {
namespace event {

const int READ_EVENT = 1;
const int WRITE_EVENT = 2;

typedef struct {
    int      fd;
    int      mask:1; 
    Closure* read_callback; 
    Closure* write_callback;
} EventFdContext;

typedef struct {
    int      time_id;
    Closure* callback;
} EventTimeContext;

class EventDriver {
public:
    virtual bool AddFdEvent(int fd, int event_type, Closure* callback) = 0;
    virtual bool DelFdEvent(int fd, int event_type) = 0;

    virtual bool AddTimeEvent(int timer_id, Closure*) = 0;
    virtual bool DelTimeEvent(int timer_id);
};

}   // ending namespace event
}   // ending namespace common

#endif  //PS_SPI_SRC/COMMON/EVENT/EVENT_DRIVER_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
