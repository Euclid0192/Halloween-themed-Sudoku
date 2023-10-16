/**
 * @file MainFrame.cpp
 * @author Nam Hai Nguyen
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sudoku", wxDefaultPosition,  wxSize( 1000,800 ));
    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxHORIZONTAL );

    auto view = new GameView();
    view->Initialize(this);

    sizer->Add(view, 1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();
}