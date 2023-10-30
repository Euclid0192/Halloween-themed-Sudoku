/**
 * @file Digit.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Digit class
 */

#include "pch.h"
#include "Digit.h"
#include "SudokuGame.h"
#include <random>

using namespace std;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;

/// If the digit comes within this distance
/// of the edge, bounce back.
const double BounceBackMargin = 10;

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
    auto tileHeight = game->GetTileHeight();
    auto tileWidth = game->GetTileWidth();

    int distX = (int)(GetX() - x);
    int distY = (int)(GetY() - tileHeight  - y);
    if (distX >= tileWidth / 2 && distX <= tileWidth * 3 / 2 && abs(distY) < tileHeight / 4)
        return true;
    return false;
}

/**
 * Update the state for ghost digit
 * @param elapsed : time has elapsed since the last update
 */
void Digit::Update(double elapsed){
    SudokuGame *game = GetGame();

    ///get the height and width for the game
    int height =  game->GetHeight();
    int width = game->GetWidth();

    ///generate random number for speed in a range
    std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
    mSpeedX = distribution(game->GetRandom());
    mSpeedY = distribution(game->GetRandom());

    auto x = Item::GetX();
    auto y = Item::GetY();

    double distanceToRight = width - x - GetWidth()/2;
    if(mSpeedX > 0 && distanceToRight <= BounceBackMargin)
    {
        mSpeedX = -mSpeedX;
    }

    double distanceToLeft = x - GetWidth()/2;
    if(mSpeedX < 0 && distanceToLeft <= BounceBackMargin)
    {
        mSpeedX = -mSpeedX;
    }

    double distanceToBottom = height - y - GetHeight()/2;
    if(mSpeedY > 0 && distanceToBottom <= BounceBackMargin)
    {
        mSpeedY = -mSpeedY;
    }

    double distanceToTop = y - GetHeight()/2;
    if(mSpeedY < 0 && distanceToTop <= BounceBackMargin)
    {
        mSpeedY = -mSpeedY;
    }

    if (game->GetLevel() == 3 && !mGiven){
        mIsGhost = TRUE;
        Floating(elapsed, mSpeedX, mSpeedY);
    }

}

/**
 * Set new location for ghost digits
 * @param elapsed : the time elapsed
 * @param speedX : the speed on along x-axis
 * @param speedY : the speed on along y-axis
 */
void Digit::Floating(double elapsed, double speedX, double speedY){

    Item::SetLocation(Item::GetX()  + mSpeedX * elapsed,
                Item::GetY()  + mSpeedY * elapsed );


}

