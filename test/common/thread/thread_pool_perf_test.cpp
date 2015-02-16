/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file thread_pool_perf_test.cpp
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/01 16:27:35
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "common/thread/thread_pool.h"
#include "common/thread/asm_atomic.h"
#include "common/util/closure.h"

using common::thread::ThreadPool;
using common::util::Closure;
using common::util::NewClosure;

ThreadPool pool(10);
volatile int task_count = 0;
volatile int preduce_num = 0;
volatile int thread_num = 0;

void TestFunc() {
    int test;
    test += 1;
    TRACE_LOG("in test func\n");
    return;
}

void* TestAddFunc(void*) {
    while (atomic_add_ret_old<int>(&thread_num, 1) < preduce_num - 1) {
        continue; 
    }
    while (atomic_add_ret_old(&task_count, -1) > 0) {
        Closure* task = NewClosure(TestFunc);  
        pool.AddTask(task);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return -1; 
    }

    preduce_num = atoi(argv[1]);
    task_count = atoi(argv[2]);

    pool.Start();
    std::vector<pthread_t> pids;
    for (int i = 0; i < preduce_num; i++) {
        pthread_t pid;
        pthread_create(&pid, NULL, TestAddFunc, NULL);
        pids.push_back(pid); 
    }

    for (int i = 0; i < preduce_num; i++) {
        pthread_join(pids[i], NULL); 
    }

    pool.Stop(true);
    return 0;
}


/* vim: set ts=4 sw=4 sts=4 tw=100 */
