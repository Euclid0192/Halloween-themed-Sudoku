/**
 * @file Background.cpp
 * @author anamo
 */

#include "pch.h"
#include "Background.h"

using namespace std;

/**
 * Constructor
 */
Background::Background(Game *game): Item(game)
{

}

/**
 * Draw the background
 * @param graphics
 */
void Background::Draw(std::shared_ptr<wxGraphicsContext> graphics)
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
    graphics->DrawBitmap(bitmap, 0, 0, image->GetWidth(), image->GetHeight());
}
