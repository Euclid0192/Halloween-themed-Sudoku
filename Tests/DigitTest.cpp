/**
 * @file HitTestTest.cpp
 * @author Nam Hai Nguyen
 *
 * A test for hit test function
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <SudokuGame.h>
#include <Digit.h>

using namespace std;

TEST(DigitTest, HitTest)
{
    SudokuGame game;
    Level level;
    level.SetGame(&game);
    level.Load(L"../levels/level1.xml");
    Digit *digit1 = new Digit(&game);

    digit1->SetLocation(100, 100);
    ASSERT_TRUE(digit1->HitTest(60, 140));
    ASSERT_TRUE(digit1->HitTest(55, 145));
    ASSERT_FALSE(digit1->HitTest(145, 110));
    ASSERT_FALSE(digit1->HitTest(55, 160));
}
