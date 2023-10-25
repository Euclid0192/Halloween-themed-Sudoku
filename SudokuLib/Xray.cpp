/**
 * @file Xray.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Xray
 */

#include "pch.h"
#include "Xray.h"
#include "Digit.h"

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
    /// Each column will have at most 4 digits to avoid out of xray
    digit->SetLocation(GetX() + mCurX * GetWidth() / 5, GetY() - mCurY * GetHeight() / 5);
    mCurY++;
    if (mCurY >= 4)
    {
        mCurX++;
        mCurY = 0;
    }
}


bool Xray::HasKey(char key)
{
	// Implement the logic to check if the X-ray holds the item corresponding to the key
	return false; // Placeholder
}