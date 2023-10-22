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
#include<cmath>

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
    SetSpeedX(MaxSpeed / 4);
    SetSpeedY(MaxSpeed / 4);
}

/**
 * Get the max speed of the Sparty
 * @return max speed of Sparty
 */
double Sparty::GetMaxSpeed()
{
    return MaxSpeed;
}

/**
 * Draw the Sparty
 * Override version of Draw inherited from Item
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

        if (mFront == 1)
        {
            graphics->DrawBitmap(mBitmap1, int(GetX()), int(GetY() - hit1 / 2), wid1, hit1);
            graphics->DrawBitmap(mBitmap2, int(GetX()), int(GetY() - hit2 / 2), wid2, hit2);
        }
        else if (mFront == 2)
        {
            graphics->DrawBitmap(mBitmap2, int(GetX()), int(GetY() - hit2 / 2), wid2, hit2);
            graphics->DrawBitmap(mBitmap1, int(GetX()), int(GetY() - hit1 / 2), wid1, hit1);
        }
    }
}

/**
 * Override version of XmlLoad for Sparty since it has two images
 * @param node : xml node that we are loading from
 */
void Sparty::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    ///Load front
    long front;
    node->GetAttribute(L"front", L"0").ToLong(&front);
    mFront = (int)front;

    ///Load mouth pivot
    double angle;
    long  x, y;
    node->GetAttribute(L"mouth-pivot-angle", L"0").ToDouble(&angle);
    node->GetAttribute(L"mouth-pivot-x", L"0").ToLong(&x);
    node->GetAttribute(L"mouth-pivot-y", L"0").ToLong(&y);
    mMouthAngle = angle;
    mMouthPivot.x = x;
    mMouthPivot.y = y;

    ///Load Head pivot
    node->GetAttribute(L"head-pivot-angle", L"0").ToDouble(&angle);
    node->GetAttribute(L"head-pivot-x", L"0").ToLong(&x);
    node->GetAttribute(L"head-pivot-y", L"0").ToLong(&y);
    mHeadAngle = angle;
    mHeadPivot.x = x;
    mHeadPivot.y = y;

    ///Load target x and y
    node->GetAttribute(L"target-x", L"0").ToLong(&x);
    node->GetAttribute(L"target-y", L"0").ToLong(&y);
    mTargetX = (int)x;
    mTargetY = (int)y;

    ///Load image paths
    wstring imagePath1 = node->GetAttribute(L"image1", L"").ToStdWstring();
    wstring imagePath2 = node->GetAttribute(L"image2", L"").ToStdWstring();

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

/**
 * Update the state of Spary
 * @param elapsed : time has elapsed since the last update
 */
void Sparty::Update(double elapsed)
{
    ///Movement
    if (!mUpdate)
        return;
    double traveledX = mSpeedX * elapsed;
    double traveledY = mSpeedY * elapsed;
    double traveled = sqrt(traveledX * traveledX + traveledY * traveledY);
    SetLocation(GetX() + (int)traveledX, GetY() + (int)traveledY);
    mTraveled += traveled;
    if (mTraveled > mDistance)
        SetUpdateState(false);

    ///Eating

}



