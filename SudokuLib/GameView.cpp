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
    Create(mainFrame, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mTimer.SetOwner(this);
    mTimer.Start(30);
    mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    mLevel.SetGame(&mGame);                                         //Makes sure that the level class knows what game class we are working with
    mLevel.Load(L"../levels/level1.xml");                   //
    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(graphics, rect.GetWidth(), rect.GetHeight());

    // Draw the scoreboard
    mScoreBoard.Draw(graphics, mGame.getScale(),mGame.getXOffset(), mGame.getYOffset());

}

/**
 * Be able to drag the sparty with the mouse
 * @param event Mouse event object
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{

}

/**
 * Handle the timer event
 * @param event
 */
void GameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}
