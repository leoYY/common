/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file test/common/util/closure_test.cpp
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/01 16:36:05
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "gtest/gtest.h"
#include "common/util/closure.h"

using common::util::Closure;

static int a = 0;

void TestFunc() {
    a = 1;
}

void TestFuncP1(int a_v) {
    a = a_v;
}

TEST(closure, closure_func_run) {
    ASSERT_TRUE(a == 0);
    Closure* callback = common::util::NewClosure(TestFunc);
    callback->Run();
    ASSERT_EQ(a, 1);
    callback = common::util::NewClosure<int>(TestFuncP1, 4);
    callback->Run();
    ASSERT_EQ(a, 4);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
