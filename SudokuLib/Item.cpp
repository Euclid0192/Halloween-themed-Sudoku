/**
 * @file Item.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Item class
 */

#include "pch.h"

#include "Item.h"
#include "SudokuGame.h"

#include<string>
using namespace std;


/**
 * Constructor
 * @param game: the game that this item is a member of
 */
Item::Item(SudokuGame *game): mGame(game)
{

}

/**
 * Copy constructor
 * @param item
 */
Item::Item(const Item &item)
{
    mGame = item.mGame;
    mId = item.mId;
    mWidth = item.mWidth;
    mHeight = item.mHeight;
    mImage = item.mImage;
    mBitmap = item.mBitmap;
}

/**
 * Destructor
 */
Item::~Item()
{
}

void Item::SetLocation(double x, double y)
{
    mLocation.m_x = x; mLocation.m_y = y;
//    auto game = GetGame();
//    double newRow = (double) ((y / game->GetTileWidth()) - 1);
//    double newCol = (double) (x / game->GetTileHeight());
//    SetColRow(newRow, newCol);
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
 * Load the declarations from xml node
 * @param node : node that we are loading from
 */
void Item::XmlLoadDeclaration(wxXmlNode *node)
{
    ///Load id
    mId = node->GetAttribute(L"id", L"").ToStdWstring();

    ///Load width and height
    long width, height;
    node->GetAttribute(L"width", L"0").ToLong(&width);
    node->GetAttribute(L"height", L"0").ToLong(&height);

    mWidth = (int)width;
    mHeight = (int)height;
    ///Load image path
    wstring imagePath = node->GetAttribute(L"image", L"").ToStdWstring();
    if (!imagePath.empty())
    {
        wstring filename = GetImagesDirectory() + L"/" + imagePath;
        mImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    }
}

/**
 * Load the actual items from the xml node
 * @param node : node we are loading from
 */
void Item::XmlLoadItem(wxXmlNode *node)
{
    ///Get the row and col
    double row, col;
    node->GetAttribute(L"row", L"0").ToDouble(&row);
    node->GetAttribute(L"col", L"0").ToDouble(&col);
    mRow = (double)row;
    mCol = (double)col;
    ///Calculate the correct location (lower-left corner of item)
    double x = col * mGame->GetTileWidth();
    double y = (row - 1) * mGame->GetTileHeight();
    SetLocation(x, y);
}