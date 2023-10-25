/**
 * @file SudokuGameTest.cpp
 * @author Joanna Rodriguez Zamarron
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <SudokuGame.h>
#include <Sparty.h>

using namespace std;

TEST(SudokuGameTest, Construct){
	SudokuGame game;
}

TEST(SudokuGameTest, HitTest) {
	SudokuGame game;

	ASSERT_EQ(game.HitTest(100, 200), nullptr) <<
												   L"Testing empty game";

	shared_ptr<Sparty> sparty = make_shared<Sparty>(&game);
	game.AddItem(sparty);
	sparty->SetLocation(100, 200);

//	ASSERT_TRUE(game.HitTest(100, 200) == sparty) << L"Testing Sparty at 100, 200";

	// if hit a place where there is no sparty image, returns a nullptr
	ASSERT_TRUE(game.HitTest(500, 500) == nullptr);
}