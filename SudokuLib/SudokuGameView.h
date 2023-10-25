/**
 * @file SudokuGameView.h
 * @author Nam Hai Nguyen, Olivia Pal
 *
 * Class that implements the child window our program draws in.
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_GAMEVIEW_H
#define ACTIONSUDOKU_SUDOKULIB_GAMEVIEW_H

#include "SudokuGame.h"
#include "ScoreBoard.h"
#include "Level.h"
#include "CompletionChecker.h"

class SudokuGameView : public wxWindow
{
private:
    ///The main game
    SudokuGame mGame;
    ///The current level
    Level mLevel;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    CompletionChecker mChecker;

public:
    void Initialize(wxFrame *mainFrame);
    void OnPaint(wxPaintEvent &event);
	void OnLeftDown(wxMouseEvent &event);
    void OnKeyDown(wxKeyEvent &event);
    void OnTimer(wxTimerEvent &event);
    void LoadLevel0();
    void LoadLevel1();
    void LoadLevel2();
    void LoadLevel3();
    void Solve();


    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
};

#endif //ACTIONSUDOKU_SUDOKULIB_GAMEVIEW_H
