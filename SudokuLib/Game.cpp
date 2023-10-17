/**
 * @file Game.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Game
 */

#include "pch.h"
#include "Game.h"
#include "Item.h"
#include "Declaration.h"
#include "Sparty.h"
#include "Digit.h"
#include "Xray.h"
#include "SpartyDeclaration.h"
#include "XrayDeclaration.h"
#include "DigitDeclaration.h"


#include "SetGivenVisitor.h"


#include<iostream>

using namespace std;

/// Directory containing the project images
/// relative to the resources directory.
const wstring ImagesDirectory = L"/images";

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
    int pixelWidth = 1440;
    int pixelHeight = 960;

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
    wxBrush background(*wxYELLOW);

    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);
    //
    // Draw in virtual pixels on the graphics context
    //
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
    graphics->PopState();
}

/**  Add an item to the game collections of declarations
* @param item: new item to add
*/
void Game::AddDeclaration(shared_ptr<Declaration> declaration)
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
shared_ptr<Item> Game::HitTest(int x, int y)
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
///**  Handle updates for animation
//* @param elapsed The time since the last update
//*/
//void Game::Update(double elapsed)
//{
//    for (auto item : mItems)
//    {
//        item->Update(elapsed);
//    }
//}

/**
*  Clear the game data.
*
* Deletes all known items in the game
*/
void Game::Clear()
{
    mItems.clear();
}

///Whoever works on this class can continue this to handle mouse click
/**
* Handle a mouse click
* @param x X location clicked on
* @param y Y location clicked on
*/
void Game::OnLeftDown(int x, int y)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;
}


