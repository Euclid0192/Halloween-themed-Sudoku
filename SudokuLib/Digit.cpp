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
    ///Just add some offset so that the Sparty can eat digits little far from it
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
    ///If digit has been eaten, or digit is given, do nothing
    if (!game->GetFloatingDigitsState() || mEaten || mGiven)
        return;
    ///Else, handling the moving
    double gameWidth = game->GetTileWidth() * game->GetWidth();
    double gameHeight = game->GetTileHeight() * game->GetHeight();

    //get the x and y position of digits
    double x = GetX();
    double y = GetY();
    ///New Location
    double newX = GetX() + mSpeedX * elapsed;
    double newY = GetY() + mSpeedY * elapsed;
    SetLocation(newX,newY);

    ///When a digit is coming to enter the board

    if (InBoardCol(newX, newY) && InBoardRow(x, y) && !InBoardCol(x, y))
    {
        mSpeedX = -mSpeedX;
    }
    if (InBoardRow(newX, newY) && InBoardCol(x, y) && !InBoardRow(x, y))
    {
        mSpeedY = -mSpeedY;
    }


    //calculation for digits bounce back
    //when hit the frame edge
    if (mSpeedX > 0 && newX >= gameWidth - GetWidth())
    {
        mSpeedX = -mSpeedX;
    }
    else if (mSpeedX < 0 && newX <= 0)
    {
        mSpeedX = -mSpeedX;
    }
    if (mSpeedY > 0 && newY >= gameHeight - GetHeight())
    {
        mSpeedY = -mSpeedY;
    }
    if (mSpeedY < 0 && newY <= 0)
    {
        mSpeedY = -mSpeedY;
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
        SetLocation(newX,newY);
    }
}

bool Digit::InBoardRow(double x, double y)
{
    SudokuGame *game = GetGame();
    auto solution = game->GetSolution();

    int rowPlay = solution->GetRow();
    double rowCur =  y / game->GetTileWidth();
    double insideBoardRow = rowCur >= rowPlay - 1 && rowCur < rowPlay + 9;
    return insideBoardRow;
}

bool Digit::InBoardCol(double x, double y)
{
    SudokuGame *game = GetGame();
    auto solution = game->GetSolution();

    int colPlay = solution->GetCol();
    double colCur =  x / game->GetTileHeight();
    double insideBoardCol = colCur >= colPlay - 1 && colCur < colPlay + 9;
    return insideBoardCol;
}