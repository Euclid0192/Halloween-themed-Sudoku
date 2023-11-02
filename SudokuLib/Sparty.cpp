/**
 * @file Sparty.cpp
 * @author Nam Hai Nguyen
 * @author Joanna Rodriguez Zamarron
 *
 * Implementation of Sparty
 */

#include "pch.h"
#include "Sparty.h"
#include "Xray.h"
#include "SudokuGame.h"
#include "GetDigitFromItem.h"
#include "Solver.h"
#include "GetGridItemVisitor.h"
#include "ContainerVisitor.h"

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
 * @param game: the game owning this Sparty
 */
Sparty::Sparty(SudokuGame *game): Item(game)
{

}


/**
 * Draw the Sparty
 * Override version of Draw inherited from Item
 * @param graphics: graphics context to draw
 */
void Sparty::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    if (mImage1 != nullptr && mImage2 != nullptr)
    {
        ///image for the head
        mBitmap1 = graphics->CreateBitmapFromImage(*mImage1);
        int wid1 = mImage1->GetWidth();
        int hit1 = mImage1->GetHeight();

        ///image for the mouth
        mBitmap2 = graphics->CreateBitmapFromImage(*mImage2);
        int wid2 = mImage2->GetWidth();
        int hit2 = mImage2->GetHeight();
        ///Headbutt rotation
		if (mHeadButt)
		{
			graphics->PushState();

			graphics->Translate(GetX() + wid1/4, GetY() + hit1);
			graphics->Rotate(mHeadAngleUpdate);
			graphics->Translate(-(GetX()+ wid1/4), -(GetY() + hit1));

		}

        if (mFront == 1)
        {
            graphics->DrawBitmap(mBitmap1, GetX(), GetY(), wid1, hit1);
            if (mEat || mSpit)
            {
                graphics->PushState();

                graphics->Translate(GetX() + mMouthPivot.x, GetY() + mMouthPivot.y);
                graphics->Rotate(mMouthAngle);
                graphics->Translate(-(GetX()  + mMouthPivot.x), -(GetY() + mMouthPivot.y));

                graphics->DrawBitmap(mBitmap2, GetX(), GetY() , wid2, hit2);
                graphics->PopState();
            }
            else
                graphics->DrawBitmap(mBitmap2, GetX(), GetY() , wid2, hit2);
        }
        else if (mFront == 2)
        {
            if (mEat || mSpit)
            {
                graphics->PushState();

                graphics->Translate(GetX() + mMouthPivot.x, GetY() + mMouthPivot.y);
                graphics->Rotate(mMouthAngleUpdate);
                graphics->Translate(-(GetX()  + mMouthPivot.x), -(GetY() + mMouthPivot.y));

                graphics->DrawBitmap(mBitmap2, GetX(), GetY() , wid2, hit2);
                graphics->PopState();
            }
            else
                graphics->DrawBitmap(mBitmap2, GetX(), GetY(), wid2, hit2);
            	graphics->DrawBitmap(mBitmap1, GetX(), GetY(), wid1, hit1);
        }
        ///Update drawing when headbutting
		if (mHeadButt)
		{
			graphics->PopState(); // Restore the state
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
 * Update the state of Sparty
 * @param elapsed : time has elapsed since the last update
 */
void Sparty::Update(double elapsed)
{
	/// Headbutting
	HeadButtAction(elapsed);

    ///Movement
    if (mMove)
        MoveAction(elapsed);

    ///Eating
    if (mEat)
        MouthUpdate(elapsed, L"Eat");

    ///Regurgitating
    if (mSpit)
        MouthUpdate(elapsed, L"Spit");
}

/**
 * The movement of Sparty
 * @param elapsed: time since last call to this function
 */
void Sparty::MoveAction(double elapsed)
{
    auto d = mSpeed * MaxSpeed * elapsed;
    double traveled = d.GetVectorLength();
    SetLocation(GetX() + d.m_x, GetY() + d.m_y);
    mTraveled += traveled;
    if (mTraveled > mDistance)
    {
        SetMoveState(false);
    }
}

/**
 * Start the eating timer
 */
void Sparty::StartMouthTimer()
{
    mMouthTime = EatingTime;
}
/**
 * Eating action of Sparty
 * @param elapsed : time since last called
 */
void Sparty::EatAction(double elapsed)
{
    ///Handling real eating
    auto game = GetGame();

    auto item = game->HitTest(GetX(), GetY());
    if (item == nullptr)
        return;
    ///If there is a digit in eating range
    GetDigitFromItem visitor;
    item->Accept(&visitor);
    auto digit = visitor.GetDigit();
    if (digit == nullptr)
        return;

    if (!digit->GetIsGhost() || !game->GetFloatingDigitsState())
        mXray->AddDigit(digit);
}

/**
 * Regurgitating action of Sparty
 * @param elapsed : time since last call
 */
void Sparty::Regurgitation(double elapsed)
{
    ///Handling spitting digits
    auto game = GetGame();
    auto solution = game->GetSolution();
    int rowPlay = solution->GetRow();
    int colPlay = solution->GetCol();

    int rowCur = round( GetY() / game->GetTileWidth() + 1);
    int colCur = round( GetX() / game->GetTileHeight() + 1 );

    ///If in board
    if (colCur < colPlay + 9 && colCur >= colPlay && rowCur >= rowPlay && rowCur < rowPlay + 9)
    {
        ///Check if something is already there
        GetGridItemVisitor gridVisitor;
        gridVisitor.SetLocation(colCur, rowCur);
        game->Accept(&gridVisitor);
        ///If something is there already, no regurgitation
        if (gridVisitor.GetResult()){
            game->AddPopup(L"Something is already there!");
            return;
        }
        ///If nothing there, spit the digits
        int value = mKeyCode - '0';
        mXray->Spit(rowCur, colCur, value);
    }
}

/**
 * Update mouth motion for eating and regurgitating
 * @param elapsed : time since last call
 * @param action : eat or regurgitate (spit)
 */
void Sparty::MouthUpdate(double elapsed, wstring action)
{
    if (mMouthTime > 0)
    {
        mMouthTime -= elapsed;
        // Calculate the percentage of the eating completed
        double percentage = 1 - (mMouthTime / EatingTime);

        if (percentage <= 0.5)
        {
            mMouthAngleUpdate = mMouthAngle * (percentage/0.5);
        }
        else
        {
            mMouthAngleUpdate = mMouthAngle *  (1 - ((percentage - 0.5) / 0.5));
        }
        if (mMouthTime <= 0)
        {
            mMouthTime = 0;
            if (action ==L"Eat")
            {
                EatAction(elapsed);
                mEat = false;
            }
            else if (action == L"Spit")
            {
                Regurgitation(elapsed);
                mSpit = false;
            }
            mMouthAngleUpdate = 0;
        }
    }
}

/**
 * Update the time of Sparty HeadButt
 */
void Sparty::StartHeadButtTimer()
{
	// Set the headbutt timer to the specified time
	mHeadButtTimeUpdate = HeadbuttTime;
}

/**
 * The action of Sparty HeadButt
 * @param elapsed : time of the event initializing
 */
void Sparty::HeadButtAction(double elapsed)
{
	mHeadButtDistance = MaxSpeed * HeadbuttTime;

	// if the headbutt timer has started
	if (mHeadButtTimeUpdate > 0)
	{
		// subtract the started headbutt timer with the elapsed to get current
		mHeadButtTimeUpdate -= elapsed;

		// Calculate the percentage of the headbutt completed
		double percentage = 1 - (mHeadButtTimeUpdate / HeadbuttTime);

		// if we are still not halfway with the angle as we rotate
		if (percentage <= 0.5)
		{
			// update the angle so that sparty is rotating forward
			mHeadAngleUpdate = mHeadAngle * (percentage/0.5);
		}

		// otherwise we are at the halfway point
		else
		{
			// let's change the angle, so we can go back to normal state
			mHeadAngleUpdate = mHeadAngle *  (1 - ((percentage - 0.5) / 0.5));

			ContainerVisitor ContainerVisitor;
			GetGame()->Accept(&ContainerVisitor);

			for(auto container : ContainerVisitor.GetContainers())
			{
				if(container->HitTest(GetX(), GetY()))
				{
					container->Empty();
				}
			}
		}

		// once the timer of the headbutt ends
		if (mHeadButtTimeUpdate <= 0)
		{
			// reset everything
			mHeadButtTimeUpdate = 0;
			mHeadButt = false;
			mHeadAngleUpdate = 0;
		}

	}
}

/**
 * Override load item from xml since location is not right in xml
 * @param node: node we are loading from
 */
void Sparty::XmlLoadItem(wxXmlNode *node)
{
    Item::XmlLoadItem(node);
    SetLocation(GetX(), GetY() - GetHeight() / 2);
}


