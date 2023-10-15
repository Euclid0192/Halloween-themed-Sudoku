/**
 * @file SudokuApp.cpp
 * @author Nam Hai Nguyen
 */

#include "pch.h"

#include "SudokuApp.h"
#include "MainFrame.h"

/**
 * Initialize the application.
 * @return
 */
bool SudokuApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();

    frame->SetFocus();
    frame->Raise();
    frame->Show(true);

    return true;
}
