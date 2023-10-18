/**
 * @file ScoreBoard.cpp
 * @author anamo
 * @author Yaxuan Tang
 *
 * The class for Scoreboard
 */

#include "pch.h"
#include <wx/graphics.h>
#include "ScoreBoard.h"
#include <sstream>

using namespace std;

/**
 * Constructor
 */
ScoreBoard::ScoreBoard(){

    mTime = 0;
    mTimer.SetOwner(this);
    mTimer.Start(1000);

    Bind(wxEVT_TIMER, &ScoreBoard::UpdateTime, this);
}

/**
 * Draw the timer
 * @param graph reference to graph been draw
 */
void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graph) {

    ///Set up the font
    ///The color needs to changed to white when the background loads properly
    wxGraphicsFont clock = graph ->CreateFont(ScoreboardTextSize, L"Timer", wxFONTFLAG_DEFAULT, *wxRED);
    graph -> SetFont(clock);

    ///Set up minutes and seconds
    wstringstream minutes, seconds;
    minutes << mTime/60 << ends;
    seconds << mTime%60 << ends;

    ///Draw the minutes and seconds
    graph -> DrawText(minutes.str(), ScoreboardTopLeft.x + 64, ScoreboardTopLeft.y);
    graph -> DrawText(L":", ScoreboardTopLeft.x + 50, ScoreboardTopLeft.y);
    graph -> DrawText(seconds.str(),ScoreboardTopLeft.x,ScoreboardTopLeft.y);

//    graphics->SetPen(wxColour(24, 69, 59));
//    wxFont font(ScoreboardTextSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
//    graphics->SetFont(font);
//    wxString timeStr = wxString::Format("%02d:%02d", mMinutes, mSeconds);
//    graphics->DrawText(timeStr, ScoreboardTopLeft);
}

void ScoreBoard::UpdateTime(wxTimerEvent& event)
{
    mTime++;
}
