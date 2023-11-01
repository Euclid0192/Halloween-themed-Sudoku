/**
 * @file SudokuGameView.cpp
 * @author Olivia Pal
 */

#include "pch.h"
#include "SudokuGameView.h"

#include <wx/dcbuffer.h>
#include<vector>

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Constructor
 * @param mainFrame Pointer to wxFrame object, the main frame for the application
 */
void SudokuGameView::Initialize(wxFrame* mainFrame)
{
    Create(mainFrame, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &SudokuGameView::OnPaint, this);
    ///Bind the mouse event handlers to the events
    Bind(wxEVT_LEFT_DOWN, &SudokuGameView::OnLeftDown, this);
    ///Bind timer event handlers to the events
    Bind(wxEVT_TIMER, &SudokuGameView::OnTimer, this);
    ///Bind the key event handlers to the events
    mainFrame->Bind(wxEVT_CHAR_HOOK, &SudokuGameView::OnKeyDown, this);


    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
    mGame.SetLevel(&mLevel);
    mLevel.SetGame(&mGame);
    mLevel.Load(L"../levels/level1.xml");
    mGame.SetCurrentLevel(1);

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SudokuGameView::OnPaint(wxPaintEvent &event)
{
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;
    mGame.Update(elapsed);
    ///Drawing objects

    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
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
void SudokuGameView::OnLeftDown(wxMouseEvent &event)
{

    int currentLevel = mGame.GetLevel();

    // If it's level 3, stop the floating digits with a click
    if (currentLevel == 3)
    {
        mGame.SetFloatingDigitsState(false);
    }

    mGame.OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Handle the timer event
 * @param event
 */
void SudokuGameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}

/**
 * Key Press handler
 * @param event : key event
 */
void SudokuGameView::OnKeyDown(wxKeyEvent &event)
{
    mGame.OnKeyDown(event);
}
/**
 * Level load handler for level 0
 * @param event
 */
void SudokuGameView::LoadLevel0()
{
    mGame.Clear();
   mLevel.Load(L"../levels/level0.xml");
}
/**
 * Level load handler for level 1
 * @param event
 */
void SudokuGameView::LoadLevel1()
{
    mGame.Clear();
    mLevel.Load(L"../levels/level1.xml");
}
/**
 * Level load handler for level 2
 * @param event
 */
void SudokuGameView::LoadLevel2()
{
    mGame.Clear();
    mLevel.Load(L"../levels/level2.xml");
}
/**
 * Level load handler for level 3
 * @param event
 */
void SudokuGameView::LoadLevel3()
{
    mGame.Clear();
    mLevel.Load(L"../levels/level3.xml");
    mGame.SetFloatingDigitsState(true);
}
/**
 * Solve game handler
 * @param event
 */
void SudokuGameView::Solve()
{
    mGame.Solve();
}

/**
* Set the level for introduction page
 * @param level, the current level
*/
void SudokuGameView::SetGameLevel(int level){
    mGame.SetCurrentLevel(level);
};