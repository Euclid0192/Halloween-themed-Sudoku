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
    SudokuGame *game = GetGame();
    mValue = digit.mValue;
    mGiven = digit.mGiven;

    std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
    mSpeedX = distribution(game->GetRandom());
    mSpeedY = distribution(game->GetRandom());

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

    //get the x and y position of digits
    double x = Item::GetX();
    double y = Item::GetY();

    //calculation for digits bounce back
    //when hit the frame edge
    if(mSpeedX > 0 && x >= 900)
    {
        mSpeedX = -mSpeedX;
    }

    else if (mSpeedX < 0 && x <= 0)
    {
        mSpeedX = -mSpeedX;
    }

    if(mSpeedY > 0 && y >= 700)
    {
        mSpeedY = -mSpeedY;
    }

    else if(mSpeedY < 0 && y <= 0)
    {
        mSpeedY = -mSpeedY;
    }

    //check if in level3 and is digits
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

    // store new position for ghost digits
    double newX;
    double newY;

    if (mIsGhost){
        newX = GetX() + mSpeedX * elapsed;
        newY = GetY() + mSpeedY * elapsed;
    }

    Item::SetLocation(newX,newY);

}

