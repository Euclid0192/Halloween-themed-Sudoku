/**
 * @file XrayTest.cpp
 * @author Olivia Pal
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <SudokuGame.h>
#include <Xray.h>

using namespace std;

TEST(XrayTest, Construct)
{
    SudokuGame game;
    Xray xray(SudokuGame* game);
}