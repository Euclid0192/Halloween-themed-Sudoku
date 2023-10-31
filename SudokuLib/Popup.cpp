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
    double wid = mGame->GetTileWidth() * mGame->GetWidth();
    double hit = mGame->GetTileHeight() * mGame->GetHeight();
    // Draw a filled rectangle
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(*wxBLACK_PEN);
    graphics->DrawRectangle(mLocation.m_x, mLocation.m_y, wid / 2, PopupHeight);

    //Set the font for levels
    wxFont bigFont(wxSize(0, 30),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(500, 0, 0));
    graphics->GetTextExtent(L"Centered Text", &wid, &hit);

    //Draw different headings for different levels
    graphics->SetPen(*wxBLUE);
    graphics->DrawText(mMessage, mLocation.m_x + PopupHeight , mLocation.m_y + PopupHeight / 4);
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
