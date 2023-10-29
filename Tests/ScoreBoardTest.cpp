/**
 * @file ScoreBoardTest.cpp
 * @author yaxuan
 * Tests for scoreboard
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <ScoreBoard.h>

using namespace std;

/**
 * Constructor test
 */
TEST(ScoreBoardTest, Construct){
    ScoreBoard scoreBoard ;
}


/**
 * Tests for RefreshTime
 */
TEST(ScoreBoardTest, RefreshTime){
    ScoreBoard timer;

    //test for UpdateTime
    timer.UpdateTime(1000);
    ASSERT_EQ(1000, timer.GetTime());

    //Test for Stop
    timer.Stop();
    timer.UpdateTime(1000);
    ASSERT_EQ(1000, timer.GetTime());

    //Test for RefreshTime
    timer.RefreshTime();
    ASSERT_EQ(0, timer.GetTime());

}