// Copyright (c) 2015 Baidu.com , Inc. All Rights Reserved
// @author: yuanyi (yuan.yi.coding@gmail.com)
// @brief : 

#include "common/util/time_debuger.h"
#include <stdarg.h>

namespace common {
namespace util {

const int MAX_INFO_LEN = 1024;

TimeDeubuger::TimeDeubuger(const char* fmt, ...) 
{
    char info_buffer[MAX_INFO_LEN];
    va_list args;
    va_start(args, fmt);
    int len = snprintf(info_buffer, MAX_INFO_LEN - 1, fmt, args); 
    va_end(args);
    _log_info.assign(info_buffer);
    gettimeofday(&_start_tm, NULL);
}

}   // ending namespace util
}   // ending namespace common
