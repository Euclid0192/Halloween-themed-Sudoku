/**
 * @file SpartyDeclaration.cpp
 * @author Nam Hai Nguyen
 */

#include "pch.h"
#include "SpartyDeclaration.h"

using namespace std;

/// Character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for an eating cycles in seconds
const double EatingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

/**
 * Constructor of SpartyDeclaration
 */
SpartyDeclaration::SpartyDeclaration(Game *game): Declaration(game)
{

}

/**
 * Overriden version of XmlLoadDeclaration
 * @param node: node that we load attributes from
 */
void SpartyDeclaration::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
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
}
