/**
 * @file SudokuGame.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of SudokuGame
 */

#include "pch.h"
#include "SudokuGame.h"
#include "Item.h"
#include "Digit.h"
#include "Xray.h"
#include "Background.h"


#include<iostream>
#include<cmath>
#include <sstream>

using namespace std;

/// Directory containing the project images
/// relative to the resources directory.
const wstring ImagesDirectory = L"/images";

///Keep on track the duration of introduction page
double introDuration = 0;
///Keep on track the duration of introduction page
double resultDuration = 0;

/**
 * Constructor
 */
SudokuGame::SudokuGame()
{
    SetImagesDirectory(L".");
    mChecker.SetGame(this);

    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());
}

/**
 * Set the directory the images are stored in
 * @param dir
 */
void SudokuGame::SetImagesDirectory(const wstring &dir) {
    mImagesDirectory = dir + ImagesDirectory;
}

/**  Draw the game
* @param graphics The GDI+ graphics context to draw on
*/
void SudokuGame::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    ///Handling Virtual Pixels
    ///Whoever takes charge of implementing virtual pixels would continue on this...
    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth = mTileWidth * mWidth;
    int pixelHeight = mTileHeight * mHeight;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;

    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

   graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    //
    // Drawing a rectangle that is the playing area size
    //
    wxBrush background(*wxWHITE);

    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);
    //
    // Draw in virtual pixels on the graphics context
    //
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }

    //Draw the introduction page
    //and scoreboard
    if (IntroOn(introDuration)){
        DrawIntroPage(graphics);
    }

    if (!IntroOn(introDuration)){
        mScoreBoard.Restart();
        mScoreBoard.Draw(graphics);
    }


    if (mCorrect && resultDuration <= 3){
        DrawResult(graphics, "Level Complete!");
        mScoreBoard.Stop();

    } else if (mCorrect && resultDuration > 3){
        if (mCurrentLevel < 3)
        {
            mCurrentLevel += 1;
            ostringstream oss;
            oss << "../levels/level" << mCurrentLevel << ".xml";
            Clear();
            mLevel->Load(oss.str());
        } else {
            Clear();
            mLevel->Load(L"../levels/level3.xml");
        }

        /// Uss oss strings to make the path to the file and load that in
    }
    if (mIncorrect && resultDuration <= 3)
    {
        DrawResult(graphics, "Incorrect");
        mScoreBoard.Stop();
    } else if (mIncorrect && resultDuration > 3){
        ostringstream oss;
        oss << "../levels/level" << mCurrentLevel << ".xml";
        Clear();
        mLevel->Load(oss.str());
    }
    if(mSpartyFull){
        DrawResult(graphics, "I'm Full!");
    }



    graphics->PopState();
}

/**  Add an item to the game collections of declarations
* @param item: new item to add
*/
void SudokuGame::AddDeclaration(shared_ptr<Item> declaration)
{
    wstring id = declaration->GetId();
    mDeclarations[id] = declaration;
    ///I have stored all the declarations loaded into a map, where key is id and value is the pointer to item
    ///So that when we load the actual items in the game, we can just access its declaration without loading again

}

/**  Add an item to the game collections of actual items
* @param item: new item to add
*/
void SudokuGame::AddItem(shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**  Test an x,y click location to see if it clicked
* on some item in the game
* @param x X location
* @param y Y location
* @return Pointer to item we clicked on or nullptr if none.
*/
shared_ptr<Item> SudokuGame::HitTest(double x, double y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }
    return  nullptr;
}

/**  Move an item to the front of the list of items.
*
* Removes item from the list and adds it to the end so it
* will display last.
* @param item The item to move
*/
void SudokuGame::MoveToFront(std::shared_ptr<Item> item)
{
    auto loc = find(std::begin(mItems), std::end(mItems), item);
    if(loc != std::end(mItems))
    {
        mItems.erase(loc);
    }

    mItems.push_back(item);

}

///Needs implementation of this function
/**  Handle updates for animation
* @param elapsed The time since the last update
*/
void SudokuGame::Update(double elapsed)
{
    ///update time for instruction page
    introDuration += elapsed;

    if (mCorrect || mIncorrect)
    {
        resultDuration += elapsed;
    }

    ///update time for scoreboard after
    /// instruction page disappear
    if (!IntroOn(introDuration)){
        mScoreBoard.UpdateTime(elapsed);
    }


    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
    ///Check the status of the game after each update
    mChecker.CheckCompletion();
}

/**
*  Clear the game data.
*
* Deletes all known items in the game
*/
void SudokuGame::Clear()
{
    if (!mItems.empty())
        mItems.clear();
    mDeclarations.clear();
    mSolution.Clear();
    mCorrect = false;
    mIncorrect = false;
    introDuration = 0;
    resultDuration = 0;
    mScoreBoard.RefreshTime();
}

///Whoever works on this class can continue this to handle mouse click
/**
* Handle a mouse click
* @param x X location clicked on
* @param y Y location clicked on
*/
void SudokuGame::OnLeftDown(double x, double y)
{
    if (mSparty == nullptr)
        return;

    ///Set the distance Sparty has traveled to 0
    mSparty->SetTraveled(0);

    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;

    wxPoint2DDouble target(oX - mSparty->GetTargetX(), oY - mSparty->GetHeight() / 2 - mSparty->GetTargetY());
    auto d = target - mSparty->GetLocation();
    ///Calculate total distance we need to move
    double distance = d.GetVectorLength();
    mSparty->SetDistance(distance);

    d.Normalize();
    mSparty->SetSpeed(d);
    mSparty->SetMoveState(true);
}

/**
 * Save declarations into XML file
 * @param node
 */
void SudokuGame::SaveDeclarations(wxXmlNode *node){
    for (auto i = mDeclarations.begin(); i != mDeclarations.end(); i++){
        i->second->SaveDeclaration(node);
    }
}

/**
 * Save items into XML file
 * @param node
 */
void SudokuGame::SaveItems(wxXmlNode *node){
    for (auto i = mItems.begin(); i != mItems.end(); i++)
    {
        (*i)->SaveItem(node);
    }
}

/**
 * Accept a visitor
 * @param visitor
 */
void SudokuGame::Accept(ItemVisitor *visitor)
{
    for (auto item: mItems)
        item->Accept(visitor);
}

/**
 * Key Press Handler
 * @param event: a key event
 */
void SudokuGame::OnKeyDown(wxKeyEvent &event)
{
    auto keyCode = event.GetKeyCode();
    ///Eating digits
    if (keyCode == WXK_SPACE)
    {
        mSparty->SetEatState(true);
        mSparty->StartMouthTimer();
    }
    ///Headbutting
	else if (keyCode == 'B' || keyCode == 'b')
	{
		mSparty->SetHeadButtState(true);
		mSparty->StartHeadButtTimer();
	}
    ///Regurgitating
    else if (keyCode >= '0' && keyCode <= '9')
    {
        mSparty->SetSpitState(true);
        mSparty->StartMouthTimer();
        mSparty->SetKeyCode(keyCode);
    }
    event.Skip();
}

/**
 * Control the time of introduction page displays
 * @param introDuration a double to store the seconds already displayed
 * @return True if the page displayed less than 3 seconds
 */
bool SudokuGame::IntroOn(double introDuration){

    int shownSeconds = (int)introDuration % 60;
    int shownMinutes = (int)introDuration / 60;

    if (shownSeconds <= 3 && shownMinutes == 0){
        return TRUE;
    }

    return FALSE;
}

/**
 * Draw the introduction page
 * @param graphics a wxGraphicsContext to draw
 */
void SudokuGame::DrawIntroPage(std::shared_ptr<wxGraphicsContext> graphics){
    // Draw a filled rectangle
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(*wxBLACK);
    graphics->DrawRectangle(150, 170, 600, 350);

    //Set the font for levels
    wxFont bigFont(wxSize(0, 80),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(0, 500, 0));
    double wid = mTileWidth * mWidth;
    double hit = mTileHeight * mHeight;
    graphics->GetTextExtent(L"Centered Text", &wid, &hit);

    //Draw different headings for different levels
    if (mCurrentLevel == 1){graphics->DrawText(L"Level 1 Begin", 200,200);}

    else if (mCurrentLevel == 2){graphics->DrawText(L"Level 2 Begin", 200,200);}

    else if (mCurrentLevel == 3){graphics->DrawText(L"Level 3 Begin", 200,200);}

    else if (mCurrentLevel == 0){graphics->DrawText(L"Level 0 Begin", 200,200);}

    //set front and draw instructions
    wxFont smallFont(wxSize(0, 40),
                     wxFONTFAMILY_SWISS,
                     wxFONTSTYLE_NORMAL,
                     wxFONTWEIGHT_BOLD);
    graphics->SetFont(smallFont, wxColour(0,0,500));

    graphics->GetTextExtent(L"Centered Text", &wid, &hit);
    graphics->DrawText(L"space: Eat", 320,300);
    graphics->DrawText(L"0-8: Regurgitate", 320,375);
    graphics->DrawText(L"B: Headbutt", 320,450);
}


/**
 * Draw the introduction page
 * @param graphics a wxGraphicsContext to draw
 */
void SudokuGame::DrawResult(std::shared_ptr<wxGraphicsContext> graphics, string str){

    wxFont bigFont(wxSize(0, 80),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(0, 500, 0));

    double wid = mTileWidth * mWidth;
    double hit = mTileHeight * mHeight;
//    graphics->GetTextExtent(L"Centered Text", &wid, &hit);
    graphics->DrawText(str, wid/2 ,hit/2);

}