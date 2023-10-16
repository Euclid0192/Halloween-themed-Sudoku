/**
 * @file Item.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Item class
 */

#include "pch.h"

#include "Item.h"
#include "Game.h"

#include<string>
using namespace std;


/**
 * Constructor
 * @param game: the game that this item is a member of
 */
Item::Item(Game *game): mGame(game)
{

}

/**
 * Destructor
 */
Item::~Item()
{
}

/**
 * Test if we clicked on this item
 * @param x: X location of the click
 * @param y: Y location of the click
 * @return: true if we click on this item; false otherwise
 */
bool Item::HitTest(int x, int y)
{
    return false;
}

/**
 * Draw the item
 * @param graphics: the graphic context we use to draw
 */
void Item::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    if (mImage != nullptr)
        if(mBitmap.IsNull())
        {
            mBitmap = graphics->CreateBitmapFromImage(*mImage);
        }
    {
        int wid = mImage->GetWidth();
        int hit = mImage->GetHeight();

        //
        // Draw a bitmap
        //
        graphics->DrawBitmap(mBitmap,
                             int(GetX()),
                             int(GetY() + hit),
                             wid,
                             hit);
    }
}

/**
 * Get image directory from the game
 * @return image directory
 */
wstring Item::GetImagesDirectory()
{
    return mGame->GetImagesDirectory();
}

/**
 * Load the attributes for the real item in the board
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    ///Get image path from declaration and load image
    vector<wstring> imagePaths = mDeclaration->GetImagePaths();
    wstring imagePath = imagePaths[0];
    if (!imagePath.empty())
    {
        wstring filename = GetImagesDirectory() + L"/" + imagePath;
        mImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    }
    else
    {
        mImage.release();
    }
    ///Get the row and col
    double row, col;
    node->GetAttribute(L"row", L"0").ToDouble(&row);
    node->GetAttribute(L"col", L"0").ToDouble(&col);
    mRow = (double)row;
    mCol = (double)col;
    ///Calculate the correct location (lower-left corner of item)
    int x = (int)(col * 48);
    int y = (int)((row - 1) * 48);
    SetLocation(x, y);
}