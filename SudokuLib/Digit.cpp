/**
 * @file Digit.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Digit class
 */

#include "pch.h"
#include "Digit.h"
#include "SudokuGame.h"

using namespace std;

/**
 * Constructor
 */
Digit::Digit(SudokuGame *game): Item(game)
{

}

/**
 * Copy constructor
 */
Digit::Digit(const Digit &digit) : Item(digit)
{
    mValue = digit.mValue;
    mGiven = digit.mGiven;
}

/**
 * Load the digit declarations
 * @param node : node that we are loading from
 */
void Digit::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    long value;
    node->GetAttribute(L"value", L"0").ToLong(&value);
    mValue = (int)value;
    auto name = node->GetName();
    if (name == L"given")
        mGiven = true;
    else
        mGiven = false;
};

/**
 * Create a clone of this digit
 * @return a shared pointer to the clone
 */
shared_ptr<Item> Digit::Clone()
{
    return make_shared<Digit>(*this);
}

/**
 * Override of HitTest in Item
 * @param x : x location
 * @param y : y location
 * @return true/false whether the item is near (x, y)
 */
bool Digit::HitTest(double x, double y)
{
    if (mGiven)
        return false;
    SudokuGame *game = GetGame();
    int distX = (int)(GetX() - x);
    int distY = (int)(GetY() - y + game->GetTileHeight());
    if (distX > 0 && distX <= game->GetTileWidth() * 3 / 2 && abs(distY) < game->GetTileHeight() / 4)
        return true;
    return false;
}


