/**
 * @file IntroPage.cpp
 * @author yaxuan
 */

#include "pch.h"
#include "IntroPage.h"

/**
 * Constructor
 */
IntroPage::IntroPage(){

    mDuration.SetOwner(this);
    mDuration.Start(1000);

    //Bind(wxEVT_PAINT, &IntroPage::Draw, this);
}

/**
 * Draw the intro page
 * @param graph reference to graph been draw
 */
void IntroPage::Draw(std::shared_ptr<wxGraphicsContext> graphics) {

    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(*wxTRANSPARENT_PEN);
    graphics->DrawRectangle(180, 180, 700, 300);

    wxFont font(wxSize(0, 30),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, wxColour(0, 128, 0));
    graphics->DrawText(L"Level 1 Begin", 200, 300);


}
