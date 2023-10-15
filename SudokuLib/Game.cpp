/**
 * @file Game.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Game
 */

#include "pch.h"
#include "Game.h"
#include "Item.h"
#include "Sparty.h"
#include "Digit.h"
#include "Xray.h"

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
void Game::OnDraw(wxDC* graphics)
{
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}

/**  Add an item to the game collections of declarations
* @param item: new item to add
*/
void Game::AddDeclaration(shared_ptr<Item> item)
{
    wstring id = item->GetId();
    mDeclarations[id] = item;
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


/**  Load the game from a .game XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* @param filename The filename of the file to load the game from.
*/
void Game::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Level");
        return;
    }

    // Once we know it is open, clear the existing data
    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto node = root->GetChildren();
    ///Current node is at declarations
    auto declaration = node->GetChildren();
    for ( ; declaration; declaration = declaration->GetNext())
    {
        XmlDeclaration(declaration);
    }
    node = node->GetNext();
    ///Current node is at game solution
    ///do something...
    node = node->GetNext();
    ///Current node at items
    auto item = node->GetChildren();
    for ( ; item; item = item->GetNext())
    {
        XmlItem(item);
    }
}

/**
 * Handle an XML node for a game declaration.
 * @param node
*/
void Game::XmlDeclaration(wxXmlNode *node)
{
    // A pointer for the item we are loading
    std::shared_ptr<Item> item;

    // We have an item. What type?
    auto name = node->GetName();
    if (name == L"given" || name == L"digit")
    {
        item = make_shared<Digit>(this);
    }
    else if (name == L"sparty")
    {
        item = make_shared<Sparty>(this);
    }
    else if (name == L"xray")
    {
        item = make_shared<Xray>(this);
    }

    if (item != nullptr)
    {
        item->XmlLoadDeclaration(node);
        AddDeclaration(item);
    }
}

/**
 * Handle an XML node for a game item.
 * @param node
*/
void Game::XmlItem(wxXmlNode* node)
{
    // A pointer for the item we are loading
    std::shared_ptr<Item> item;

    // We have an item. What type?
    auto id = node->GetAttribute(L"id", L"").ToStdWstring();
    item = mDeclarations[id];
    item->XmlLoadItem(node);
    AddItem(item);
}

/**
*  Clear the game data.
*
* Deletes all known items in the game
*/
void Game::Clear()
{
    mItems.clear();
}


