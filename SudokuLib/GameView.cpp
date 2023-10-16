/**
 * @file GameView.cpp
 * @author DELL
 */

#include "pch.h"
#include "GameView.h"

#include <wx/dcbuffer.h>
#include<vector>

using namespace std;

/**
 * Constructor
 * @param mainFrame Pointer to wxFrame object, the main frame for the application
 */
void GameView::Initialize(wxFrame* mainFrame)
{
    Create(mainFrame, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    mClockTimer.Bind(wxEVT_TIMER, &GameView::OnScoreTimer, this);

    //Initialize the scoreboard timer and start it so that it sends an event every 1000 millisecond = 1 second
    mClockTimer.Start(1000);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    mGame.Load(L"../levels/level1.xml");
    mGame.OnDraw(&dc);

    //Draw the scoreboard
    //mClock.Draw(&dc);
}

/**
 * ScoreBoard event, updates the clock and redraws
 * @param event
 */
void GameView::OnScoreTimer(wxTimerEvent& event){
    mClock.UpdateTime();
    wxWindow::Refresh();
}