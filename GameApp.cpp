/**
 * @file GameApp.cpp
 *
 * @author Alex Beck
 */

#include "pch.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "GameApp.h"
#include <MainFrame.h>

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <MainFrame.h>
#endif

/**
 * Initialize the application.
 * @return
 */
bool GameApp::OnInit()
{
    // checking for memory leaks
#ifdef WIN32
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
    if (!wxApp::OnInit())
        return false;

    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}
