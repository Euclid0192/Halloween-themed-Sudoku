/**
 * @file MainFrame.cpp
 * @author Nam Hai Nguyen, Joanna Rodriguez Zamarron, Olivia Pal
 */

#include "pch.h"
#include "MainFrame.h"
#include "SudokuGameView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sudoku", wxDefaultPosition,  wxSize( 1000,800 ));
    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxHORIZONTAL );

    auto view = new SudokuGameView();
    view->Initialize(this);
    mGameView = view;

    sizer->Add(view, 1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

	auto menuBar = new wxMenuBar( );
	auto fileMenu = new wxMenu();
	auto helpMenu = new wxMenu();
	auto levelMenu = new wxMenu();

	menuBar->Append(fileMenu, L"&File" );
	menuBar->Append(levelMenu, L"&Level");
	menuBar->Append(helpMenu, L"&Help");

	fileMenu->Append(IDM_SOLVE, "Solve", "Solve the Action Sudoku board");
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

	levelMenu->Append(IDM_LEVELZERO, "Level 0", "Level 0 gameplay");
	levelMenu->Append(IDM_LEVELONE, "Level 1", "Level 1 gameplay");
	levelMenu->Append(IDM_LEVELTWO, "Level 2", "Level 2 gameplay");
	levelMenu->Append(IDM_LEVELTHREE, "Level 3", "Level 3 gameplay");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelZero, this, IDM_LEVELZERO);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelOne, this, IDM_LEVELONE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelTwo, this, IDM_LEVELTWO);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelThree, this, IDM_LEVELTHREE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnSolve, this, IDM_SOLVE);

	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

	SetMenuBar( menuBar );
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(L"Action Sudoku",
				 L"About Action Sudoku",
				 wxOK,
				 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}
void MainFrame::OnLevelZero(wxCommandEvent& event)
{

    mGameView->LoadLevel0();
}
void MainFrame::OnLevelOne(wxCommandEvent& event)
{

    mGameView->LoadLevel1();
}
void MainFrame::OnLevelTwo(wxCommandEvent& event)
{

    mGameView->LoadLevel2();
}

void MainFrame::OnLevelThree(wxCommandEvent& event)
{
    mGameView->LoadLevel3();
}

void MainFrame::OnSolve(wxCommandEvent &event)
{
    mGameView->Solve();
}