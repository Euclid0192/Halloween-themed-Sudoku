/**
 * @file Digit.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Digit class
 */

#include "pch.h"
#include "Digit.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 */
Digit::Digit(Game *game): Item(game)
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
bool Digit::HitTest(int x, int y)
{
    int distX = (int)x - GetX();
    int distY = (int)y - GetY();
    Game *game = GetGame();
    if (distX <= game->GetTileWidth() && abs(distY) <= game->GetHeight() / 4)
        return true;
    return false;
}


