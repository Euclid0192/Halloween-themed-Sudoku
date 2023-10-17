/**
 * @file Level.cpp
 * @author Lewi Anamo
 */

#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "Item.h"
#include "Declaration.h"
#include "Sparty.h"
#include "Digit.h"
#include "Xray.h"
#include "SpartyDeclaration.h"
#include "XrayDeclaration.h"
#include "DigitDeclaration.h"
#include "SetGivenVisitor.h"

#include<memory>
#include<iostream>

using namespace std;


/**  Load the game from a .game XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* @param filename The filename of the file to load the game from.
*/
void Level::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Level");
        return;
    }

    // Once we know it is open, clear the existing data
    mGame->Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    // The order of children tags in the xml file is declarations -> game -> items
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
void Level::XmlDeclaration(wxXmlNode *node)
{
    // A pointer for the item we are loading
    std::shared_ptr<Declaration> declaration = nullptr;

    // We have an item. What type?
    auto name = node->GetName();
    if (name == L"given" || name == L"digit")
    {
        declaration = std::make_shared<DigitDeclaration>(mGame);
        ///If given, set given to true
        if (name == L"given")
        {
            SetGivenVisitor visitor;
            declaration->Accept(&visitor);
        }
    }
    else if (name == L"sparty")
    {
        declaration = make_shared<SpartyDeclaration>(mGame);
    }
    else if (name == L"xray")
    {
        declaration = make_shared<XrayDeclaration>(mGame);
    }

    if (declaration != nullptr)
    {
        declaration->XmlLoad(node);
        mGame->AddDeclaration(declaration);
    }
}

/**
 * Handle an XML node for a game item.
 * @param node
*/
void Level::XmlItem(wxXmlNode* node)
{
    // A pointer for the item and declaration we are loading
    std::shared_ptr<Declaration> declaration = nullptr;
    std::shared_ptr<Item> item = nullptr;

    // We have an item. What type?
    auto id = node->GetAttribute(L"id", L"").ToStdWstring();
    declaration = mGame->GetDeclaration(&id);

    auto name = node->GetName();
    if (name == L"digit" || name == L"given")
    {
        item = make_shared<Digit>(mGame);
    }
    else if (name == L"sparty")
    {
        item = make_shared<Sparty>(mGame);
    }
    else if (name == L"xray")
    {
        item = make_shared<Xray>(mGame);
    }
    if (item != nullptr)
    {
        item->SetDeclaration(declaration);
        item->XmlLoad(node);
        mGame->AddItem(item);
    }
}