/**
 * @file Game.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Game
 */

#include "pch.h"
#include "Game.h"
#include "Item.h"
#include "Digit.h"


#include<iostream>
#include<cmath>

using namespace std;

/// Directory containing the project images
/// relative to the resources directory.
const wstring ImagesDirectory = L"/images";

///Keep on track the duration of introduction page
double introDuration = 0;

/**
 * Constructor
 */
Game::Game()
{
    SetImagesDirectory(L".");
}

/**
 * Set the directory the images are stored in
 * @param dir
 */
void Game::SetImagesDirectory(const wstring &dir) {
    mImagesDirectory = dir + ImagesDirectory;
}

/**  Draw the game
* @param graphics The GDI+ graphics context to draw on
*/
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
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

    ///Draw the introduction page
    ///and scoarboard
    if (IntroOn(introDuration)){
        DrawIntroPage(graphics);
    }

    if (!IntroOn(introDuration)){
        mScoreBoard.Draw(graphics);
    }

    graphics->PopState();
}

/**  Add an item to the game collections of declarations
* @param item: new item to add
*/
void Game::AddDeclaration(shared_ptr<Item> declaration)
{
    wstring id = declaration->GetId();
    mDeclarations[id] = declaration;
    ///I have stored all the declarations loaded into a map, where key is id and value is the pointer to item
    ///So that when we load the actual items in the game, we can just access its declaration without loading again

}

/**  Add an item to the game collections of actual items
* @param item: new item to add
*/
void Game::AddItem(shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**  Test an x,y click location to see if it clicked
* on some item in the game
* @param x X location
* @param y Y location
* @return Pointer to item we clicked on or nullptr if none.
*/
shared_ptr<Item> Game::HitTest(double x, double y)
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
void Game::MoveToFront(std::shared_ptr<Item> item)
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
void Game::Update(double elapsed)
{

    ///update time for scoreboard after
    /// instruction page disappear
    if (!IntroOn(introDuration)){
        mScoreBoard.UpdateTime(elapsed);
    }

    ///update time for instruction page
    introDuration += elapsed;

    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}

/**
*  Clear the game data.
*
* Deletes all known items in the game
*/
void Game::Clear()
{
    if (!mItems.empty())
        mItems.clear();
    mDeclarations.clear();
}

///Whoever works on this class can continue this to handle mouse click
/**
* Handle a mouse click
* @param x X location clicked on
* @param y Y location clicked on
*/
void Game::OnLeftDown(double x, double y)
{
    if (mSparty == nullptr)
        return;

    ///Set the distance Sparty has traveled to 0
    mSparty->SetTraveled(0);

    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;

    wxPoint2DDouble target(oX - mSparty->GetTargetX(), oY - mSparty->GetTargetY());
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
void Game::SaveDeclarations(wxXmlNode *node){
    for (auto i = mDeclarations.begin(); i != mDeclarations.end(); i++){
        i->second->SaveDeclaration(node);
    }
}

/**
 * Save items into XML file
 * @param node
 */
void Game::SaveItems(wxXmlNode *node){
    for (auto i = mItems.begin(); i != mItems.end(); i++)
    {
        (*i)->SaveItem(node);
    }
}

/**
 * Accept a visitor
 * @param visitor
 */
void Game::Accept(ItemVisitor *visitor)
{
    for (auto item: mItems)
        item->Accept(visitor);
}

/**
 * Key Press Handler
 * @param event: a key event
 */
void Game::OnKeyDown(wxKeyEvent &event)
{
    if (event.GetKeyCode() == WXK_SPACE)
    {
        mSparty->SetEatState(true);
        mSparty->StartEatTimer();
    }

	if (event.GetKeyCode() == 'B' || event.GetKeyCode() == 'b')
	{
		mSparty->SetHeadButtState(true);
		mSparty->StartHeadButtTimer(0.5);
	}

    event.Skip();
}

/**
 * Control the time of introduction page displays
 * @param introDuration a double to store the seconds already displayed
 * @return True if the page displayed less than 3 seconds
 */
bool Game::IntroOn(double introDuration){

    int shown = (int)introDuration % 60;

    if (shown <= 3){
        return TRUE;
    }

    return FALSE;
}

/**
 * Draw the introduction page
 * @param graphics a wxGraphicsContext to draw
 */
void Game::DrawIntroPage(std::shared_ptr<wxGraphicsContext> graphics){
    //
    // Draw a filled rectangle
    //
    wxBrush rectBrush(*wxCYAN);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(*wxTRANSPARENT_PEN);
    graphics->DrawRectangle(150, 198, 700, 350);

}

