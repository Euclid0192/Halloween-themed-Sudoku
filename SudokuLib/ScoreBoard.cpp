/**
 * @file ScoreBoard.cpp
 * @author anamo
 * @author Yaxuan Tang
 *
 * The class for Scoreboard
 */

#include "pch.h"
#include "ScoreBoard.h"


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
void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale,
                      double XOffset, double YOffset) {

    //Set the font
    wxFont font(ScoreboardTextSize,
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, *wxWHITE);

    // set the content of the text
    wxString TimeStr = wxString::Format("%2d:%02d",mTime/60,mTime%60);

    //Draw the content with virtual pixel
    //Not working very well
    graphics->PushState();
    graphics->Translate(XOffset, YOffset);
    graphics->Scale(scale, scale);
    graphics->DrawText(TimeStr, XOffset, YOffset);
    graphics->PopState();

}

void ScoreBoard::UpdateTime(wxTimerEvent &event)
{
    mTime++;
}




