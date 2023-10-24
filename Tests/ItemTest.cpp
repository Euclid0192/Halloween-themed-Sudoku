/**
 * @file ItemTest.cpp
 * @author Nam Hai Nguyen
 *
 * A test for item base class
 */


#include <pch.h>
#include "gtest/gtest.h"

#include<SudokuGame.h>
#include<Item.h>

using namespace std;

/**
*  Item mock derived object
*/
class ItemMock : public Item
{
public:
    /**  Constructor
     * @param game : game this Item is a member of
     */
    ItemMock(SudokuGame *game) : Item(game)
    {
    }

    ~ItemMock() {}
    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     * */
    virtual void Accept(ItemVisitor* visitor) override { }
};

TEST(ItemTest, Constructor)
{
    SudokuGame game;
    ItemMock item(&game);
}

TEST(ItemTest, SetLocation)
{
    SudokuGame game;
    ItemMock item(&game);

    ASSERT_EQ(0, item.GetX());
    ASSERT_EQ(0, item.GetY());

    item.SetLocation(17, 23);
    ASSERT_EQ(17, item.GetX());
    ASSERT_EQ(23, item.GetY());

    item.SetLocation(100, 100);
    ASSERT_EQ(100, item.GetX());
    ASSERT_EQ(100, item.GetY());
}

TEST(ItemTest, GameGetter)
{
    SudokuGame game;
    ItemMock item(&game);

    SudokuGame *testGame = item.GetGame();
    ASSERT_EQ(testGame, &game);
}

TEST(ItemTest, Solve)
{

}




