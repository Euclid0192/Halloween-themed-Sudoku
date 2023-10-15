/**
 * @file MainFrame.h
 * @author Nam Hai Nguyen
 *
 * The top-level (main) frame of the application
 */

#ifndef TARTARUS_SUDOKULIB_MAINFRAME_H
#define TARTARUS_SUDOKULIB_MAINFRAME_H

#include <wx/filehistory.h>
#include <wx/config.h>

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:

public:
    void Initialize();
};

#endif //TARTARUS_SUDOKULIB_MAINFRAME_H
