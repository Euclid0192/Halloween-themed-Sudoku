/**
 * @file ScoreBoard.cpp
 * @author anamo
 */

#include "pch.h"
#include "ScoreBoard.h"

/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

/// Top left corner of the scoreboard in virtual pixels
const wxPoint ScoreboardTopLeft(10, 10);

ScoreBoard::ScoreBoard(){
    mMinutes = 0;
    mSeconds = 0;
}

void ScoreBoard::UpdateTime() {
    mSeconds++;
    if (mSeconds >= 60) {
        mSeconds = 0;
        mMinutes++;
    }
}

void ScoreBoard::Draw(wxDC* graphics) {
    graphics->SetPen(wxColour(24, 69, 59));
    wxFont font(ScoreboardTextSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font);
    wxString timeStr = wxString::Format("%02d:%02d", mMinutes, mSeconds);
    graphics->DrawText(timeStr, ScoreboardTopLeft);
}
