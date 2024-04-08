/**
 * @file GameView.cpp
 * @author Alex Beck
 */
#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <memory>
#include "GameView.h"
#include "ids.h"
#include <wx/font.h>

using namespace std;

/// The time (in milliseconds) to take between frames
const int FrameDuration = 30;

/**
 * Set up the game view
 * @param parent The frame that this view is a part of
 */
void GameView::Initialize(wxFrame* parent)
{

    Create(parent, wxID_ANY,wxDefaultPosition,
           wxDefaultSize,wxFULL_REPAINT_ON_RESIZE);
    // set view as white for set up
    // will change later
    SetBackgroundColour(*wxWHITE);

    // Set background style so we can use dcbuffer
    // and OnPaint events
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind paint event
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel0, this, IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel1, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel2, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel3, this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAutoPlay, this, IDM_AUTOPLAY);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();

    mGame = make_unique<Game>(L"level1.xml");
    mLevelTextTimer.SetOwner(this, wxID_ANY);
//    mLevelTextTimer.Start(2000, wxTIMER_ONE_SHOT);
    mLevelTextTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
    Bind(wxEVT_TIMER, &GameView::OnLevelTextTimer, this, mLevelTextTimer.GetId());
    mSoloIncomingTimer.SetOwner(this, wxID_ANY);
    mGoTimer.SetOwner(this, wxID_ANY);
    mSoloEndedTimer.SetOwner(this, wxID_ANY);
    mSoloEndingMessageTimer.SetOwner(this, wxID_ANY);
    Bind(wxEVT_TIMER, &GameView::OnSoloIncomingTimer, this, mSoloIncomingTimer.GetId());
    Bind(wxEVT_TIMER, &GameView::OnGoTimer, this, mGoTimer.GetId());
    Bind(wxEVT_TIMER, &GameView::OnSoloEndedTimer, this, mSoloEndedTimer.GetId());
    Bind(wxEVT_TIMER, &GameView::OnSoloEndingMessageTimer, this, mSoloEndingMessageTimer.GetId());
    mMaxBeat=mGame->GetLevel()->GetMusic()->GetMeasures();
}
/**
 * check if the solo is coming up
 * @param event the timer we check to display its coming up
 */

void GameView::OnSoloIncomingTimer(wxTimerEvent& event)
{
    mDisplaySoloIncoming = true;
    Refresh();
    mSoloIncomingTimer.Stop();
    mGoTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
}

/**
 * starts the double time event solo
 * @param event the timer to start it up
 */

void GameView::OnGoTimer(wxTimerEvent& event)
{
    mDisplaySoloIncoming = false;
    mDisplayGo = true;
    Refresh();
    mGoTimer.Stop();
    mSoloEndedTimer.Start(mSoloDuration, wxTIMER_ONE_SHOT);

}

/**
 * end the solo event for 2x points
 * @param event the timer we use to check it ends
 */

void GameView::OnSoloEndedTimer(wxTimerEvent& event)
{
    mDisplayGo = false;
    mDisplaySoloEnded = true;
    Refresh();
    mSoloEndedTimer.Stop();
    mSoloEndingMessageTimer.Start(mSoloEndingDelay, wxTIMER_ONE_SHOT);
}

/**
 * sets the timer to show the solo ending
 * @param event the timer to set the message up
 */

void GameView::OnSoloEndingMessageTimer(wxTimerEvent& event)
{
    mDisplaySoloEnded = false;
    Refresh();
    mSoloEndingMessageTimer.Stop();
}


/**
 * refreshes the screen and toggles the level text
 * @param event the timer to start the level timer
 */
void GameView::OnLevelTextTimer(wxTimerEvent& event){
    mDisplayLevelText = false;
    Refresh();
}

/**
 * Handle redrawing the window
 * @param event The paint event
 */
void GameView::OnPaint(wxPaintEvent &event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc = shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;
    mGame->Update(elapsed);

    wxRect rect = GetRect();
    mGame->OnDraw(gc, rect.GetWidth(), rect.GetHeight());

    if (mDisplayLevelText)
    {
        // Draw level begin text
        wxString mLevelText = wxString::Format("Level %d Begin", mCurrentLevel);
        wxFont font(100, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gc->SetFont(font, *wxCYAN);

        double textWidth, textHeight;
        gc->GetTextExtent(mLevelText, &textWidth, &textHeight);

        // Center the text in the view
        double xPos = (rect.GetWidth() - textWidth) / 2;
        double yPos = (rect.GetHeight() - textHeight) / 2.5;
        gc->DrawText(mLevelText, xPos, yPos);
    }
	if(playing && !mDisplayLevelText)
	{
        playing = false;
		mGame->Play();
	}

    wxString mSoloText;
    if (mDisplaySoloIncoming) mSoloText = "Solo incoming!";
    else if (mDisplayGo)
	{
		mSoloText = "Go!";
		mGame->SoloSwitch(true);
	}
    else if (mDisplaySoloEnded)
	{
		mSoloText = "Solo ended!";
		mGame->SoloSwitch(false);
	}

    if (mMaxBeat*4-8 <= mGame->GetLevel()->GetCurrentBeat())
    {
        mSoloText="Level Complete!";
    }
    if (mMaxBeat*4-4 <= mGame->GetLevel()->GetCurrentBeat())
    {
        if(mCurrentLevel==0)
        {
            mGame->LoadLevel(L"level1.xml");
            mCurrentLevel = 1;
            mDisplayLevelText = true;
            playing = true;
            mLevelTextTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
            mMaxBeat=mGame->GetLevel()->GetMusic()->GetMeasures();
            mDisplaySoloIncoming = false;
            mDisplayGo = false;
            mDisplaySoloEnded = false;
            Refresh();
        }
        else if(mCurrentLevel==1)
        {
            mGame->LoadLevel(L"level2.xml");
            mCurrentLevel = 2;
            mDisplayLevelText = true;
            playing = true;
            mLevelTextTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
            mMaxBeat=mGame->GetLevel()->GetMusic()->GetMeasures();
            mDisplaySoloIncoming = false;
            mDisplayGo = false;
            mDisplaySoloEnded = false;
            Refresh();
        }
        else if(mCurrentLevel==2)
        {
            mGame->LoadLevel(L"level3.xml");
            mCurrentLevel = 3;
            mDisplayLevelText = true;
            playing = true;
            mLevelTextTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
            mMaxBeat=mGame->GetLevel()->GetMusic()->GetMeasures();
            mDisplaySoloIncoming = false;
            mDisplayGo = false;
            mDisplaySoloEnded = false;
            Refresh();
            mSoloIncomingTimer.Start(mSoloDelay, wxTIMER_ONE_SHOT);
        }
        else
        {
            mGame->LoadLevel(L"level1.xml");
            mCurrentLevel = 1;
            mDisplayLevelText = true;
            playing = true;
            mLevelTextTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
            mMaxBeat=mGame->GetLevel()->GetMusic()->GetMeasures();
            mDisplaySoloIncoming = false;
            mDisplayGo = false;
            mDisplaySoloEnded = false;
            Refresh();
        }
    }

    if (!mSoloText.empty())
    {
        wxFont font(50, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gc->SetFont(font, *wxCYAN);
        double textWidth, textHeight;
        gc->GetTextExtent(mSoloText, &textWidth, &textHeight);
        double xPos = (rect.GetWidth() - textWidth) / 2;
         double yPos = (rect.GetHeight() - textHeight) / 4;
        gc->DrawText(mSoloText, xPos, yPos);
    }



}
/**
 * Handle the left mouse button down event
 * @param event The moust click event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame->OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Handle key press event
 * @param event The key event
 */
void GameView::OnKeyDown(wxKeyEvent &event)
{
    if (event.IsAutoRepeat())
        return;
    mGame->OnKeyDown(event.GetUnicodeKey());
}

/**
 * Handle key release event
 * @param event The key event
 */
void GameView::OnKeyUp(wxKeyEvent &event)
{
    mGame->OnKeyUp(event.GetUnicodeKey());
}

/**
* Loads level 0
* @param event the event to start level 0
*/
void GameView::OnLoadLevel0(wxCommandEvent& event)
{
    mGame->LoadLevel(L"level0.xml");
    mCurrentLevel = 0;
    mDisplayLevelText = true;
    playing = true;
    mLevelTextTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
    mMaxBeat=mGame->GetLevel()->GetMusic()->GetMeasures();
    mDisplaySoloIncoming = false;
    mDisplayGo = false;
    mDisplaySoloEnded = false;
    Refresh();
}

/**
 * Loads level 1
 * @param event the event to start level 1
 */

void GameView::OnLoadLevel1(wxCommandEvent& event)
{
    mGame->LoadLevel(L"level1.xml");
    mCurrentLevel = 1;
    mDisplayLevelText = true;
	playing = true;
    mLevelTextTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
    mMaxBeat=mGame->GetLevel()->GetMusic()->GetMeasures();
    mDisplaySoloIncoming = false;
    mDisplayGo = false;
    mDisplaySoloEnded = false;
    Refresh();
}

/**
 * Loads level 2
 * @param event the event to start level 2
 */
void GameView::OnLoadLevel2(wxCommandEvent& event)
{
    mGame->LoadLevel(L"level2.xml");
    mCurrentLevel = 2;
    mDisplayLevelText = true;
	playing = true;
    mLevelTextTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
    mMaxBeat=mGame->GetLevel()->GetMusic()->GetMeasures();
    mDisplaySoloIncoming = false;
    mDisplayGo = false;
    mDisplaySoloEnded = false;
    Refresh();
}
/**
 * Loads level 3
 * @param event the event to start level 3
 */
void GameView::OnLoadLevel3(wxCommandEvent& event)
{
    mGame->LoadLevel(L"level3.xml");
    mCurrentLevel = 3;
    mDisplayLevelText = true;
	playing = true;
    mLevelTextTimer.Start(mGame->GetLevel()->GetMusic()->BeatsToSeconds(mBeatsInMeasure) * mOneSecond, wxTIMER_ONE_SHOT);
    mMaxBeat=mGame->GetLevel()->GetMusic()->GetMeasures();
    mDisplaySoloIncoming = false;
    mDisplayGo = false;
    mDisplaySoloEnded = false;
    Refresh();
    mSoloIncomingTimer.Start(mSoloDelay, wxTIMER_ONE_SHOT);

}

/**
 * Turns on autoplay
 * @param event the event to toggle the autoplay
 */
void GameView::OnAutoPlay(wxCommandEvent& event)
{
    mGame->SetAutoPlay();
}

/**
 * Handle a timer event by redrawing the window
 * @param event The timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}
