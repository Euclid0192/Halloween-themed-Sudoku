/**
 * @file Sparty.cpp
 * @author Nam Hai Nguyen
 * @author Joanna Rodriguez Zamarron
 *
 * Implementation of Sparty
 */

#include "pch.h"
#include "Sparty.h"
#include "SudokuGame.h"
#include "GetDigitFromItem.h"
#include "Solver.h"

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
Sparty::Sparty(SudokuGame *game): Item(game)
{

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
        ///image for the head
        mBitmap1 = graphics->CreateBitmapFromImage(*mImage1);
        int wid1 = mImage1->GetWidth();
        int hit1 = mImage1->GetHeight();

        ///image for the mouth
        mBitmap2 = graphics->CreateBitmapFromImage(*mImage2);
        int wid2 = mImage2->GetWidth();
        int hit2 = mImage2->GetHeight();

		if (mHeadButt)
		{
			graphics->PushState();

			graphics->Translate(GetX() + wid1/4, GetY() + hit1/2);
			graphics->Rotate(mHeadAngleUpdate);
			graphics->Translate(-(GetX()+ wid1/4), -(GetY() + hit1/2));

		}

        if (mFront == 1)
        {
            graphics->DrawBitmap(mBitmap1, GetX(), GetY() - hit1 / 2, wid1, hit1);
            if (mEat || mSpit)
            {
                graphics->PushState();

                graphics->Translate(GetX() + mMouthPivot.x, GetY() - hit2 / 2 + mMouthPivot.y);
                graphics->Rotate(mMouthAngle);
                graphics->Translate(-(GetX()  + mMouthPivot.x), -(GetY() + mMouthPivot.y));

                graphics->DrawBitmap(mBitmap2, GetX(), GetY() , wid2, hit2);
                graphics->PopState();
            }
            else
                graphics->DrawBitmap(mBitmap2, GetX(), GetY() - hit2 / 2, wid2, hit2);
        }
        else if (mFront == 2)
        {
            if (mEat || mSpit)
            {
                graphics->PushState();

                graphics->Translate(GetX() + mMouthPivot.x, GetY() - hit2 / 2 + mMouthPivot.y);
                graphics->Rotate(mMouthAngleUpdate);
                graphics->Translate(-(GetX()  + mMouthPivot.x), -(GetY() + mMouthPivot.y));

                graphics->DrawBitmap(mBitmap2, GetX(), GetY() , wid2, hit2);
                graphics->PopState();
            }
            else
                graphics->DrawBitmap(mBitmap2, GetX(), GetY() - hit2 / 2, wid2, hit2);
            	graphics->DrawBitmap(mBitmap1, GetX(), GetY() - hit1 / 2, wid1, hit1);
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
    MoveAction(elapsed);

    ///Eating
    EatAction(elapsed);

    ///Regurgitating
    Regurgitation(elapsed);
}

/**
 * The movement of Sparty
 * @param elapsed: time since last call to this function
 */
void Sparty::MoveAction(double elapsed)
{
    if (!mMove)
        return;

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
    if (!mEat)
        return;

    MouthUpdate(elapsed, L"Eat");
    ///Handling real eating
    auto game = GetGame();
    auto item = game->HitTest(GetX(), GetY());
    if (item == nullptr)
        return;
    ///If there is a digit in eating range
    GetDigitFromItem visitor;
    item->Accept(&visitor);
    auto digit = visitor.GetDigit();
    mXray->AddDigit(digit);
}

/**
 * Regurgitating action of Sparty
 * @param elapsed : time since last call
 */
void Sparty::Regurgitation(double elapsed)
{
    if (!mSpit)
        return;

    MouthUpdate(elapsed, L"Spit");
    ///Handling spitting digits
    auto game = GetGame();
    auto solution = game->GetSolution();
    int rowPlay = solution->GetRow();
    int colPlay = solution->GetCol();
    int colCur = (int) (GetCol() + 1) + 1;
    int rowCur = (int)(GetRow()) + 1;

    ///If in board
    if (colCur < colPlay + 9 && colCur >= colPlay && rowCur >= rowPlay && rowCur < rowPlay + 9)
    {
        mXray->Spit(rowCur, colCur);
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
                mEat = false;
            else if (action == L"Spit")
                mSpit = false;
            mMouthAngleUpdate = 0;
        }
    }
}

/**
 * Update the time of Sparty HeadButt
 * @param time : time of the event initializing
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
	if (mHeadButtTimeUpdate > 0)
	{
		mHeadButtTimeUpdate -= elapsed;
		// Calculate the percentage of the headbutt completed
		double percentage = 1 - (mHeadButtTimeUpdate / HeadbuttTime);

		if (percentage <= 0.5)
		{
			mHeadAngleUpdate = mHeadAngle * (percentage/0.5);
		}
		else
		{
			mHeadAngleUpdate = mHeadAngle *  (1 - ((percentage - 0.5) / 0.5));
		}

		if (mHeadButtTimeUpdate <= 0)
		{
			mHeadButtTimeUpdate = 0;
			mHeadButt = false;
			mHeadAngleUpdate = 0;
		}

		else
		{
			//check for containers
		}
	}
}


