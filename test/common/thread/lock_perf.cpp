/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file test/common/thread/lock_perf.cpp
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/17 00:43:16
 * @version $Revision$ 
 * @brief performance on mutex vs spin vs atomic
 *      ./lock_perf input_threads output_threads prod_counts lock_type
 **/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include "common/thread/asm_atomic.h"

const int ATOMIC = 1;
const int MUTEX = 2;
const int SPIN = 3;
static int LOCKTYPE;
volatile int PRODCOUNTS = 0;
volatile int THREADS_NUM = 0;
volatile int CUR_THRD_NUM = 0;

pthread_mutex_t MUTEXLOCK;
pthread_spinlock_t SPINLOCK;
volatile int VALUE = 0;

void* TestFuncMutex(void*) {
    atomic_add_ret_old(&CUR_THRD_NUM, 1);
    while (true) {
        if (atomic_add_ret_old(&CUR_THRD_NUM, 0) >= THREADS_NUM - 1) 
            break;
    }

    while(true) {
        pthread_mutex_lock(&MUTEXLOCK);
        VALUE += 1;
        if (VALUE >= PRODCOUNTS)
            break;
        pthread_mutex_unlock(&MUTEXLOCK);
    }
    return NULL;
}

void* TestFuncSpin(void*) {
    atomic_add_ret_old(&CUR_THRD_NUM, 1);
    while (true) {
        if (atomic_add_ret_old(&CUR_THRD_NUM, 0) >= THREADS_NUM - 1) 
            break;
    }
    while(true) {
        pthread_spin_lock(&SPINLOCK); 
        VALUE += 1;
        if (VALUE >= PRODCOUNTS)
            break;
        pthread_spin_unlock(&SPINLOCK);
    }
    return NULL;
}

void* TestFuncAtomic(void*) {
    atomic_add_ret_old(&CUR_THRD_NUM, 1);
    while (true) {
        if (atomic_add_ret_old(&CUR_THRD_NUM, 0) >= THREADS_NUM - 1) 
            break;
    }
    while (true) {
        if (atomic_add_ret_old(&VALUE, 1) >= PRODCOUNTS)
            break;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(
                stderr, 
                "input err: ./lock_perf threads prod_counts lock_type\n"); 
        return -1;
    }
    THREADS_NUM = atoi(argv[1]);
    PRODCOUNTS = atoi(argv[2]);
    LOCKTYPE = atoi(argv[3]);
    
    std::vector<pthread_t> pids;
    for (int i = 0; i < THREADS_NUM; i++) {
        pthread_t pid; 
        switch (LOCKTYPE) {
        case ATOMIC:
            pthread_create(&pid, NULL, TestFuncAtomic, NULL);
            break;
        case MUTEX:
            pthread_create(&pid, NULL, TestFuncMutex, NULL);
            break;
        case SPIN:
            pthread_create(&pid, NULL, TestFuncSpin, NULL);
            break;
        default : 
            return -1;
        }
        pids.push_back(pid);
    }

    for (size_t i = 0; i < pids.size(); i++) {
        pthread_join(pids[i], NULL);
    }
    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
