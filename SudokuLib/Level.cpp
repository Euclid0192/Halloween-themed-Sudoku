/**
 * @file Level.cpp
 * @author Lewi Anamo
 */

#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "Item.h"
#include "Digit.h"
#include "Xray.h"
#include "Background.h"
#include "Container.h"
#include "GetSpartyVisitor.h"

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
    root->GetAttribute(L"width").ToInt(&mScreenWidth);
    root->GetAttribute(L"height").ToInt(&mScreenHeight);
    root->GetAttribute(L"tilewidth").ToInt(&mTileWidth);
    root->GetAttribute(L"tileheight").ToInt(&mTileHeight);
    mGame->SetTileDimension(mTileWidth, mTileHeight);
    mGame->SetGameDimension(mScreenWidth, mScreenHeight);

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

    ///Calling load function in Solver class
    Solver* solution = mGame->GetSolution();
    solution->XmlLoad(node);

    node = node->GetNext();
    ///Current node at items
    auto item = node->GetChildren();
    for ( ; item; item = item->GetNext())
    {
        XmlItem(item);
    }

    GetSpartyVisitor visitor;
    mGame->Accept(&visitor);
    Sparty *sparty = visitor.GetSparty();
    mGame->SetSparty(sparty);
}

/**
 * Handle an XML node for a game declaration.
 * @param node
*/
void Level::XmlDeclaration(wxXmlNode *node)
{
    // A pointer for the item we are loading
    std::shared_ptr<Item> declaration = nullptr;

    // We have an item. What type?
    auto name = node->GetName();
    if (name == L"given" || name == L"digit")
    {
        declaration = make_shared<Digit>(mGame);
    }
    else if (name == L"sparty")
    {
        declaration = make_shared<Sparty>(mGame);
    }
    else if (name == L"xray")
    {
        declaration = make_shared<Xray>(mGame);
    }
    else if (name == L"background")
    {
        declaration = make_shared<Background>(mGame);
    }
    else if (name == L"container")
    {
        declaration =  make_shared<Container>(mGame);
    }

    if (declaration != nullptr)
    {
        declaration->XmlLoadDeclaration(node);
        mGame->AddDeclaration(declaration);
    }
}

/**
 * Handle an XML node for a game item.
 * @param node
*/
void Level::XmlItem(wxXmlNode* node)
{
    auto id = node->GetAttribute(L"id", L"").ToStdWstring();
    auto declaration = mGame->GetDeclaration(id);
    shared_ptr<Item> item = declaration;
    auto name = node->GetName();

    if (declaration != nullptr)
    {
        ///If digit, have to make a clone
        if (name == L"digit" || name ==L"given")
        {
            item = declaration->Clone();
        }
        item->XmlLoadItem(node);
        mGame->AddItem(item);
    }
}

/**
 * Save the level as a .xml XML file.
 *
 * Open an XML file and stream the game data to it.
 *
 * @param filename The filename of the file to save the level to
 */
void Level::Save(const wxString &filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"level");
    xmlDoc.SetRoot(root);

    root->AddAttribute(L"width", wxString::FromDouble(mScreenWidth));
    root->AddAttribute(L"height", wxString::FromDouble(mScreenHeight));
    root->AddAttribute(L"tilewidth", wxString::FromDouble(mTileWidth));
    root->AddAttribute(L"tileheight", wxString::FromDouble(mTileHeight));

    auto declarationNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"declarations");
    root->AddChild(declarationNode);

    mGame->SaveDeclarations(declarationNode);

    auto gameNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"game");
    root->AddChild(gameNode);

    Solver* solution = mGame->GetSolution();
    solution->XmlSave(gameNode);

    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"items");
    root->AddChild(itemNode);

    mGame->SaveItems(itemNode);

    if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}