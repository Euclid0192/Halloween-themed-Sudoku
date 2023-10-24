/**
 * @file Container.cpp
 * @author yaxuan
 *
 * Class for containers
 *
 */


#include "pch.h"
#include "Container.h"
#include "Item.h"
#include "Game.h"

using namespace std;

/// Get container pumpkin image
const wstring Pumpkin = L"images/pumpkin.png";
const wstring PumpkinFront = L"images/pumpkin-front.png";

/// Get container cauldron image
const wstring cauldron = L"images/cauldron.png";
//const wstring cauldron-2 = L"images/cauldron-2.png";

/**
 * Constructor
 */
Container::Container(Game *game) : Item(game)
{

}

/**
 * Override draw function
 * @param graphics : graphics context we use to draw
 */
void Container::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    auto wid = GetWidth(), hit = GetHeight();
    ///Get the bitmap and image of the background
    auto bitmap = Item::GetBitmap();
    auto image = Item::GetImage();

    ///Check if the bitmap is null
    if(bitmap.IsNull())
    {
        bitmap = graphics->CreateBitmapFromImage(*image);
    }

    ///Draw the back image
    graphics->DrawBitmap(bitmap,
                         GetX(),
                         GetY() - hit,
                         wid,
                         hit
    );
    if(mFrontBitmap.IsNull())
    {
        mFrontBitmap = graphics->CreateBitmapFromImage(*mFrontImage);
    }

    ///Draw the digits inside
    for (auto digit: mDigits)
    {
        digit->Draw(graphics);
    }

    //
    // Draw the front image
    //
    graphics->DrawBitmap(mFrontBitmap,
                         GetX(),
                         GetY() - hit,
                         wid,
                         hit);
}
/**
 * Override of loading declarations
 * @param node : node we are loading
 */
void Container::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    auto frontPath = node->GetAttribute(L"front", L"").ToStdWstring();
    frontPath = GetImagesDirectory() + L"/" + frontPath;
    if (!frontPath.empty())
        mFrontImage = std::make_unique<wxImage>(frontPath, wxBITMAP_TYPE_ANY);
}

/**
 * Override of loading items
 * @param node : node we are loading
 */
void Container::XmlLoadItem(wxXmlNode *node)
{
    Item::XmlLoadItem(node);
    auto game = GetGame();
    ///Loading all the digits inside the container
    auto child = node->GetChildren();
    for ( ; child; child = child->GetNext())
    {
        auto id = child->GetAttribute(L"id", L"").ToStdWstring();
        auto declaration = game->GetDeclaration(id);
        auto item = declaration->Clone();
        item->XmlLoadItem(child);
        item->SetLocation(item->GetX(), item->GetY() - 2 * item->GetHeight());
        mDigits.push_back(item);
    }
}

