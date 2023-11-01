/**
 * @file Popup.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Popup
 */

#include "pch.h"
#include "Popup.h"
#include "SudokuGame.h"

using namespace std;
///Speed of popup
const int PopupSpeed = 400;
///Height of popup
const int PopupHeight = 50;

/**
 * Constructor
 */
Popup::Popup(SudokuGame *game, wstring message) : mGame(game), mMessage(message)
{
    double wid = game->GetTileWidth() * game->GetWidth();
    double hit = game->GetTileHeight() * game->GetHeight();
    SetLocation(wid / 4, hit);
}

/**
 * Draw this pop up with the given graphic context
 * @param graphics: graphics context used to draw
 */
void Popup::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    ///We only cares about width and X-location since the popup
    ///will start at bottom and fly to the top
    double wid = mGame->GetTileWidth() * mGame->GetWidth();
    double textWidth, textHeight;
    //Set the font for levels
    wxFont bigFont(wxSize(0, 30),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(500, 0, 0));
    graphics->GetTextExtent(mMessage, &textWidth, &textHeight);
    ///This location is to maintain the center position of the popup
    SetLocation((wid - textWidth - textHeight) / 2, mLocation.m_y);
    // Draw a filled rectangle
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(*wxBLACK_PEN);
    ///Add textHeight to textWidth and textHeight for some blank space around the text
    graphics->DrawRectangle(mLocation.m_x, mLocation.m_y, textWidth + textHeight, textHeight * 2);
    ///The location is for centering the text in the box
    graphics->DrawText(mMessage, mLocation.m_x + textHeight / 2 , mLocation.m_y + textHeight / 2);
}

/**
 * Making the popup moving from bottom to top
 * @param elapsed: time since last update
 */
void Popup::Update(double elapsed)
{
    double newX = mLocation.m_x;
    double newY = mLocation.m_y - elapsed * PopupSpeed;
    SetLocation(newX, newY);
    if (newY < 0)
    {
        mGame->RemovePopup(this);
    }
}
