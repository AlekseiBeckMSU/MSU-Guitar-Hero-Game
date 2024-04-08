/**
 * @file MainFrame.cpp
 *
 * @author Alex Beck
 */

#include "pch.h"
#include "ids.h"
#include "MainFrame.h"
#include "GameView.h"
#include "Game.h"

/**
 * Initialize Game
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"SpartanHero",
           wxDefaultPosition, wxSize(1304,900));

    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    mGameView = new GameView();
    mGameView->Initialize(this);

    sizer->Add(mGameView,1, wxEXPAND | wxALL );

    SetSizer( sizer );
    Layout();

    auto menuBar = new wxMenuBar();

    auto fileMenu = new wxMenu();
    auto levelsMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    menuBar->Append(levelsMenu, L"&Level" );
    levelsMenu->Append(IDM_LEVEL0, L"&Level 0", L"Level 0");
    levelsMenu->Append(IDM_LEVEL1, L"&Level 1", L"Level 1");
    levelsMenu->Append(IDM_LEVEL2, L"&Level 2", L"Level 2");
    levelsMenu->Append(IDM_LEVEL3, L"&Level 3", L"Level 3");

    levelsMenu->AppendSeparator();
    levelsMenu->Append(IDM_AUTOPLAY, L"&Auto Play", "Auto Play Level", wxITEM_CHECK);

    menuBar->Append(helpMenu, L"&Help");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    SetMenuBar(menuBar);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}
/**
 * Handle a clsoe event. Stop animation and destorys window
 * @param event  the clos event
 */
void MainFrame::OnClose(wxCloseEvent & event)
{
    mGameView->Stop();
    Destroy();
}
/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(L"Spartan Hero",
                 L"Spartan Hero by Philip Glass",
                 wxOK,
                 this);
}
