/**
 * @file GameView.cpp
 * @author DELL
 */

#include "pch.h"
#include "GameView.h"

#include <wx/dcbuffer.h>
#include<vector>

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Constructor
 * @param mainFrame Pointer to wxFrame object, the main frame for the application
 */
void GameView::Initialize(wxFrame* mainFrame)
{
    Create(mainFrame, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    ///Bind the mouse event handlers to the events
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
    mLevel.SetGame(&mGame);
    mLevel.Load(L"../levels/level1.xml");
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event)
{
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;
    mGame.Update(elapsed);
    ///Drawing objects

    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(graphics, rect.GetWidth(), rect.GetHeight());

//    // Draw the scoreboard
//    mScoreBoard.Draw(graphics);

}

/**
 * Be able to drag the sparty with the mouse
 * @param event Mouse event object
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Handle the timer event
 * @param event
 */
void GameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}
