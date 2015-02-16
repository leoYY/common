/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file src/common/util/log.h
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/16 13:44:31
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef _COMMON_UTIL_LOG_H
#define _COMMON_UTIL_LOG_H

const int TRACE_LEVEL = 16;
const int DEBUG_LEVEL = 8;
const int INFO_LEVEL = 4;
const int WARNING_LEVEL = 2;
const int FATAL_LEVEL = 1;

static int global_log_level = 4;

#define FATAL_LOG(_fmt_, args...) \
    do {\
        if (global_log_level >= FATAL_LEVEL) { \
            fprintf(stderr, _fmt_, ##args);\
        } \
    } while(0) 

#define WARNING_LOG(_fmt_, args...) \
    do {\
        if (global_log_level >= WARNING_LEVEL) {\
            fprintf(stderr, _fmt_, ##args);\
        } \
    } while(0)

#define DEBUG_LOG(_fmt_, args...) \
    do {\
        if (global_log_level >= DEBUG_LEVEL) { \
            fprintf(stdout, _fmt_, ##args);\
        } \
    } while(0) 

#define INFO_LOG(_fmt_, args...) \
    do {\
        if (global_log_level >= INFO_LEVEL) {\
            fprintf(stdout, _fmt_, ##args);\
        } \
    } while(0)

#define TRACE_LOG(_fmt_, args...) \
    do {\
        if (global_log_level >= TRACE_LEVEL) {\
            fprintf(stderr, _fmt_, ##args);\
        } \
    } while(0)

#endif  

/* vim: set ts=4 sw=4 sts=4 tw=100 */
