/**
 * @file MainFrame.h
 * @author Nam Hai Nguyen
 *
 * The top-level (main) frame of the application
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_MAINFRAME_H
#define ACTIONSUDOKU_SUDOKULIB_MAINFRAME_H

#include "SudokuGameView.h"

#include <wx/filehistory.h>
#include <wx/config.h>

/**
 *
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// The pointer to the game view of this game
    SudokuGameView *mGameView = nullptr;
public:
    void Initialize();

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);
    void OnSolve(wxCommandEvent& event);
    void OnLevelZero(wxCommandEvent& event);
    void OnLevelOne(wxCommandEvent& event);
    void OnLevelTwo(wxCommandEvent& event);
    void OnLevelThree(wxCommandEvent& event);
};

#endif //ACTIONSUDOKU_SUDOKULIB_MAINFRAME_H
