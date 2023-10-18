/**
 * @file Sparty.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Sparty
 */

#include "pch.h"
#include "Sparty.h"
#include "Game.h"

#include<string>
using namespace std;

/// Character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for an eating cycles in seconds
const double EatingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

/**
 * Constructor of Sparty
 */
Sparty::Sparty(Game *game): Item(game)
{
    mSpeedX = MaxSpeed / 2;
    mSpeedY = MaxSpeed / 2;
}

/**
 * Draw the Sparty
 * Overriden version of Draw inherited from Item
 * @param dc: device context to draw
 */
void Sparty::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    if (mImage1 != nullptr && mImage2 != nullptr)
    {
        mBitmap1 = graphics->CreateBitmapFromImage(*mImage1);
        int wid1 = mImage1->GetWidth();
        int hit1 = mImage1->GetHeight();


        mBitmap2 = graphics->CreateBitmapFromImage(*mImage2);
        int wid2 = mImage2->GetWidth();
        int hit2 = mImage2->GetHeight();

        graphics->DrawBitmap(mBitmap1, int(GetX()), int(GetY()), wid1, hit1);
        graphics->DrawBitmap(mBitmap2, int(GetX()), int(GetY()), wid2, hit2);
    }
}

/**
 * Override version of XmlLoad for Sparty since it has two images
 * @param node : xml node that we are loading from
 */
void Sparty::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    shared_ptr<Declaration> declaration = GetDeclaration();
    vector<wstring> imagePaths = declaration->GetImagePaths();
    wstring imagePath1 = imagePaths[0], imagePath2 = imagePaths[1];

    if (!imagePath1.empty() && !imagePath2.empty())
    {
        wstring filename1 = GetImagesDirectory() + L"/" + imagePath1;
        mImage1 = std::make_unique<wxImage>(filename1, wxBITMAP_TYPE_ANY);
        wstring filename2 = GetImagesDirectory() + L"/" + imagePath2;
        mImage2 = std::make_unique<wxImage>(filename2, wxBITMAP_TYPE_ANY);
    }
    else
    {
        mImage1.release();
        mImage2.release();
    }
}


