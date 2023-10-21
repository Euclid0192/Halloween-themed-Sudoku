/**
 * @file ScoreBoard.cpp
 * @author anamo
 * @author Yaxuan Tang
 *
 * The class for Scoreboard
 */

#include "pch.h"
#include "ScoreBoard.h"
#include <sstream>
#include <iomanip>

using namespace std;

/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

/// Top left corner of the scoreboard in virtual pixels
const wxPoint ScoreboardTopLeft(10, 10);


///**
// * Draw the timer
// * @param graph reference to graph been draw
// */
//void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale,
//                      double XOffset, double YOffset) {
//
//    //Set the font
//    wxFont font(ScoreboardTextSize,
//                wxFONTFAMILY_SWISS,
//                wxFONTSTYLE_NORMAL,
//                wxFONTWEIGHT_BOLD);
//    graphics->SetFont(font, *wxWHITE);
//
//    // set the content of the text
//    wxString TimeStr = wxString::Format("%2d:%02d",mTime/60,mTime%60);
//
//
//    //Draw the content with virtual pixel
//    //Not working very well
//    graphics->PushState();
//    graphics->Translate(XOffset, YOffset);
//    graphics->Scale(scale, scale);
//    graphics->DrawText(TimeStr, XOffset - ScoreboardTopLeft.x, YOffset - ScoreboardTopLeft.y);
//    graphics->PopState();
//
//}


//    ///Check if the bitmap is null
//    if(bitmap.IsNull())
//    {
//        bitmap = graphics->CreateBitmapFromImage(*image);
//    }
//
//    ///Draw the background
//    graphics->DrawBitmap(bitmap, 0, 0, image->GetWidth(), image->GetHeight());


ScoreBoard::ScoreBoard() {

}

void ScoreBoard::UpdateTime(double elapsed)
{
    mTime += elapsed;

}

void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mTime == 0)
    {
        return;
    }

    int minutes = (int)mTime/60;
    int seconds = (int)mTime%60;
    auto font = graphics->CreateFont(ScoreboardTextSize,L"Arial",wxFONTFLAG_BOLD, *wxWHITE);
    graphics->SetFont(font);

    std::wstringstream text;

    text << std::setw(2) << std::setfill(L' ') << minutes << L":" << std::setw(2) << std::setfill(L'0') << seconds << std::ends;

    graphics->DrawText(text.str(), ScoreboardTopLeft.x, ScoreboardTopLeft.y);

}





