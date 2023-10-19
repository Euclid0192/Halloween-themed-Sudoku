/**
 * @file GameView.h
 * @author Nam Hai Nguyen
 *
 * Class that implements the child window our program draws in.
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_GAMEVIEW_H
#define ACTIONSUDOKU_SUDOKULIB_GAMEVIEW_H

#include "Game.h"
#include "ScoreBoard.h"
#include "IntroPage.h"
#include "Level.h"

class GameView : public wxWindow
{
private:
    ///The main game
    Game mGame;
    ///The current level
    Level mLevel;
    ///The score board
    ScoreBoard mScoreBoard;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

public:
    void Initialize(wxFrame *mainFrame);
    void OnPaint(wxPaintEvent &event);
	void OnLeftDown(wxMouseEvent &event);
    void OnTimer(wxTimerEvent &event);
};

#endif //ACTIONSUDOKU_SUDOKULIB_GAMEVIEW_H
