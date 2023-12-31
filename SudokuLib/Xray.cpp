/**
 * @file Xray.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Xray
 */

#include "pch.h"
#include "Xray.h"
#include "Digit.h"
#include "SudokuGame.h"
#include <algorithm>

using namespace std;

///Maximum number of digits in a column in the Xray
const int MaxDigitCol = 4;

/**
 * Constructor
 * @param game game we will be drawing on and connecting to
 */
Xray::Xray(SudokuGame *game): Item(game)
{

}

/**
 * Override XmlLoadDeclaration
 * @param node: node that we load attributes from
 */
void Xray::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    long capacity;
    node->GetAttribute(L"capacity", L"0").ToLong(&capacity);
    mCapacity = (int) capacity;
}

/**
 * Override draw function for xray due to offset position
 * @param graphics : graphics context used to draw
 */
void Xray::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    ///Get the bitmap and image of the background
    auto bitmap = GetBitmap();
    auto image = GetImage();

    ///Check if the bitmap is null
    if(bitmap.IsNull())
    {
        bitmap = graphics->CreateBitmapFromImage(*image);
    }

    ///Draw the background
    ///Has to minus offset because of location from xml out of background
    graphics->DrawBitmap(bitmap,
                         GetX(),
                         GetY() - GetHeight() * 2 / 3,
                         GetWidth(),
                         GetHeight()
    );
}

/**
 * Add a digit to xray
 * @param digit : digit to be added
 */
void Xray::AddDigit(Digit *digit)
{
    /// Use this for full
    auto game = GetGame();
    if(mDigits.size() >= mCapacity)
    {
        game->AddPopup(L"I'm Full");
        return;
    }

    ///Check if the digit is already in Xray
    if (digit->GetEaten())
        return;
    
    Relocate(digit);
    digit->SetEaten(true);
    mDigits.push_back(digit);

}

/**
 * A function to move the digit into the Xray without overlapping
 * @param digit : digit to be relocated
 */
void Xray::Relocate(Digit *digit)
{
    ///Display the digits in the Xray in rows and columns so that they are not overlapping

    ///Calculating new coordinates
    auto game = GetGame();
    double newX = GetX() + mCurX * GetWidth() / (MaxDigitCol + 1);
    double newY = GetY() - mCurY * GetHeight() / (MaxDigitCol + 1);
    double row =  GetY() / game->GetTileWidth();
    double col = GetX() / game->GetTileHeight();

    digit->SetLocation(newX, newY);
    digit->SetColRow(row, col);
    mCurY++;
    /// Each column will have at most 4 digits to avoid out of xray
    if (mCurY >= MaxDigitCol)
    {
        mCurX++;
        mCurY = 0;
    }
    if (mCurX >= MaxDigitCol)
    {
        mCurX = 0;
        mCurY = 0;
    }
}

/**
 * Performs the spitting action of the numbers from sparty's stomach
 * @param row row location of where to spit
 * @param col column location of where to spit
 * @param value the value of the digit we are looking for
 */
void Xray::Spit(int row, int col, int value)
{
    /// Use this for full
    auto game = GetGame();
    if (mDigits.size() == 0)
        return;

    Digit *digit = nullptr;
    for (auto d: mDigits)
    {
        if (d->GetValue() == value)
        {
            digit = d;
            break;
        }
    }

    ///Digit not in stomach
    if (digit == nullptr)
        return;
    ///Else
    Remove(digit);
    ///Set location on board
    int x = col * game->GetTileWidth();
    int y = row * game->GetTileHeight();
    digit->SetLocation(x, y);
    digit->SetColRow(row, col);
    ///Make it edible again
    digit->SetEaten(false);
    digit->SetIsGhost(false);
}

/**
* Remove a digit from the Xray
* @param digit pointer to the digit we need to remove
*/
void Xray::Remove(Digit *digit)
{
    auto loc = find(mDigits.begin(), mDigits.end(), digit);
    if (loc != mDigits.end())
    {
        mDigits.erase(loc);
        digit->SetEaten(false);

    }
    
}