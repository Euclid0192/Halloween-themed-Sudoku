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

class GameView : public wxWindow
{
private:
    ///The main game
    Game mGame;

    Level mLevel;

    ScoreBoard mScoreBoard;

public:
    void Initialize(wxFrame *mainFrame);
    void OnPaint(wxPaintEvent &event);
	void OnLeftDown(wxMouseEvent &event);
};

#endif //ACTIONSUDOKU_SUDOKULIB_GAMEVIEW_H
