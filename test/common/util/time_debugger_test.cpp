/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file time_debuger_test.cpp
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2015/02/16 12:19:55
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "gtest/gtest.h"
#include "common/util/time_debuger.h"

using common::util::TimerDebuger;


TEST(timerdebuger, test_info) {
    TimerDebuger debugger("test info %s", "hehe"); 
    ASSERT_EQ(debugger._log_info, "test info hehe"); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/* vim: set ts=4 sw=4 sts=4 tw=100 */
