/**
 * @file Xray.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Xray
 */

#include "pch.h"
#include "Xray.h"

using namespace std;

/**
 * Constructor
 */
Xray::Xray(Game *game): Item(game)
{

}

/**
 * Override XmlLoadDeclaration
 * @param node: node that we load attributes from
 */
void Xray::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    long capacity;
    node->GetAttribute(L"capacity", L"0").ToLong(&capacity);
    mCapacity = (int) capacity;
}

void Xray::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    ///Get the bitmap and image of the background
    auto bitmap = Item::GetBitmap();
    auto image = Item::GetImage();

    ///Check if the bitmap is null
    if(bitmap.IsNull())
    {
        bitmap = graphics->CreateBitmapFromImage(*image);
    }

    ///Draw the background
    graphics->DrawBitmap(bitmap,
                         GetX(),
                         GetY() - GetHeight() / 3,
                         GetWidth(),
                         GetHeight()
    );
}