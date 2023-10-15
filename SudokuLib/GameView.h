/**
 * @file GameView.h
 * @author Nam Hai Nguyen
 *
 * Class that implements the child window our program draws in.
 */

#ifndef TARTARUS_SUDOKULIB_GAMEVIEW_H
#define TARTARUS_SUDOKULIB_GAMEVIEW_H

#include "Game.h"

class GameView : public wxWindow
{
private:
    ///The main game
    Game mGame;
public:
    void Initialize(wxFrame *mainFrame);
    void OnPaint(wxPaintEvent &event);
};

#endif //TARTARUS_SUDOKULIB_GAMEVIEW_H
