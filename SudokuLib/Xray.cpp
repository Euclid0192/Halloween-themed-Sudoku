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

using namespace std;

/**
 * Constructor
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

void Xray::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    ///Get the bitmap and image of the background
    auto bitmap = Item::GetBitmap();
    auto image = Item::GetImage();

    ///Check if the bitmap is null
    if(bitmap.IsNull())
    {
        bitmap = graphics->CreateBitmapFromImage(*image);
    }

    ///Draw the background
    graphics->DrawBitmap(bitmap,
                         GetX(),
                         GetY() - GetHeight() / 3,
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
    if (mDigits.size() >= mCapacity)
        return;

    ///Check if the digit is already in Xray
    for (auto item: mDigits)
    {
        if (item == digit)
            return;
    }
    
    Relocate(digit);
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
    double newX = GetX() + mCurX * GetWidth() / 5;
    double newY = GetY() - mCurY * GetHeight() / 5;
    ///Calculating new rows and cols
    double newRow = (double) (newX / game->GetTileWidth());
    double newCol = (double) (newY / game->GetTileHeight() + 1);
    digit->SetColRow(newRow, newCol);
    digit->SetLocation(newX, newY);
    mCurY++;
    /// Each column will have at most 4 digits to avoid out of xray
    if (mCurY >= 4)
    {
        mCurX++;
        mCurY = 0;
    }
}