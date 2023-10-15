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
 *  Set the image file to draw
 * @param path
 */
void Item::SetImage(const std::wstring &path)
{
    if (!path.empty())
    {
        std::wstring filename = mGame->GetImagesDirectory() + L"/" + path;
        mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
        mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
    }
    else
    {
        mItemImage.release();
        mItemBitmap.release();
    }
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
 * @param dc: the device context we use to draw
 */
void Item::Draw(wxDC *dc)
{
    if (mItemImage != nullptr)
    {
        int wid = mItemImage->GetWidth();
        int hit = mItemImage->GetHeight();

        dc->DrawBitmap(*mItemBitmap,
                       int(GetX() - wid / 2),
                       int(GetY() - hit / 2));
    }
}

/**
 * Load the attributes for an item node in the declaration.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
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
    SetImage(imagePath);
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
void Item::XmlLoadItem(wxXmlNode *node)
{
    ///Get the row and col
    long row, col;
    node->GetAttribute(L"row", L"0").ToLong(&row);
    node->GetAttribute(L"col", L"0").ToLong(&col);
    SetRow(row);
    SetCol(col);
    ///Calculate the correct location (lower-left corner of item)
    int x = (int)col * mWidth;
    int y = (int)(row - 1) * mHeight;
    SetLocation(x, y);
}