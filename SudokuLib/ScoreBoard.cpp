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

///Store boolean to see if timer is running
bool IsRunning = TRUE;

/**
 * Constrcutor
 */
ScoreBoard::ScoreBoard() {

}

/**
 * Update time for scoreboard
 * @param elapsed a double to track on time
 */
void ScoreBoard::UpdateTime(double elapsed)
{
    if (IsRunning){
        mTime += elapsed;
    }

    else {
        mTime += 0;
    }

}

/**
 * Refresh the scoreboard when changing levels
 */
void ScoreBoard::RefreshTime()
{
    mTime = 0;

}

/**
 * Stop the Timer
 */
void ScoreBoard::Stop()
{
    IsRunning = FALSE;

}

/**
 * Restart the Timer
 */
void ScoreBoard::Restart()
{
    IsRunning = TRUE;

}

/**
 * Draw the scoreboard
 * @param graphics a wxGraphicsContext to draw
 */
void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    int minutes = (int)mTime/60;
    int seconds = (int)mTime%60;
    auto font = graphics->CreateFont(ScoreboardTextSize,L"Arial",wxFONTFLAG_BOLD, *wxWHITE);
    graphics->SetFont(font);

    std::wstringstream text;

    text << std::setw(2) << std::setfill(L' ') << minutes << L":" << std::setw(2) << std::setfill(L'0') << seconds << std::ends;

    graphics->DrawText(text.str(), ScoreboardTopLeft.x, ScoreboardTopLeft.y);

}





