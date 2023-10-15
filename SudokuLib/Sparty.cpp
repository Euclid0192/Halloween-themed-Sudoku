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
    SetLocation(200, 200);
}

/**
 * Draw the Sparty
 * Overriden version of Draw inherited from Item
 * @param dc: device context to draw
 */
void Sparty::Draw(wxDC *dc)
{
    if (mImage1 != nullptr && mImage2 != nullptr)
    {
        int wid1 = mImage1->GetWidth();
        int hit1 = mImage1->GetHeight();

        dc->DrawBitmap(*mBitmap1,
                       int(GetX() - wid1 / 2),
                       int(GetY() - hit1 / 2));

        int wid2 = mImage2->GetWidth();
        int hit2 = mImage2->GetHeight();

        dc->DrawBitmap(*mBitmap2,
                       int(GetX() - wid1 / 2 ),
                       int(GetY() - hit1 / 2 ));
    }
}

/**
 * Set the pivot value angle, x, and y
 * @param pivot: the pivot we need to set
 * @param angle: pivot angle
 * @param x: pivot x
 * @param y: pivot y
 */
void Sparty::SetPivot(Pivot &pivot, double angle, int x, int y)
{
    pivot.angle = angle;
    pivot.x = x;
    pivot.y = y;
}

/**
 * Overriden version of XmlLoadDeclaration
 * @param node: node that we load attributes from
 */
void Sparty::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    ///Load images' paths
    wstring SpartyImage1 = node->GetAttribute(L"image1", L"").ToStdWstring();
    wstring SpartyImage2 = node->GetAttribute(L"image2", L"").ToStdWstring();

    SpartyImage1 = L"./images/" + SpartyImage1;
    SpartyImage2 = L"./images/" + SpartyImage2;

    mImage1 = make_unique<wxImage>(SpartyImage1, wxBITMAP_TYPE_ANY);
    mImage2 = make_unique<wxImage>(SpartyImage2, wxBITMAP_TYPE_ANY);
    mBitmap1 = make_unique<wxBitmap>(*mImage1);
    mBitmap2 = make_unique<wxBitmap>(*mImage2);

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
    SetPivot(mMouthPivot, angle, x, y);

    ///Load Head pivot
    node->GetAttribute(L"head-pivot-angle", L"0").ToDouble(&angle);
    node->GetAttribute(L"head-pivot-x", L"0").ToLong(&x);
    node->GetAttribute(L"head-pivot-y", L"0").ToLong(&y);
    SetPivot(mHeadPivot, angle, x, y);

    ///Load target x and y
    node->GetAttribute(L"target-x", L"0").ToLong(&x);
    node->GetAttribute(L"target-y", L"0").ToLong(&y);
    mTargetX = (int)x;
    mTargetY = (int)y;
}

