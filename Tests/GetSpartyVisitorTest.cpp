/**
 * @file GetSpartyVisitorTest.cpp
 * @author Nam Hai Nguyen
 *
 * A test for GetSpartyVisitor
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <SudokuGame.h>
#include <GetSpartyVisitor.h>
#include <Sparty.h>

using namespace std;

TEST(VisitorTest, GetSpartyVisitor)
{
    SudokuGame game;

    GetSpartyVisitor visitor;
    game.Accept(&visitor);

    Sparty *sparty1 = visitor.GetSparty();
    ASSERT_TRUE(sparty1 == nullptr);

    std::shared_ptr<Sparty> sparty2 = std::make_shared<Sparty>(&game);
    game.AddItem(sparty2);
    game.Accept(&visitor);
    sparty1 = visitor.GetSparty();
    ASSERT_FALSE(sparty1 == nullptr);
}
