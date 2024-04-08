/**
 * @file GameView.h
 * @author Alex Beck
 *
 * GameView class that handles drawing/loading of levels
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_GAMEVIEW_H
#define SPARTANHERO_SPARTANHEROLIB_GAMEVIEW_H

#include <memory>
#include "Game.h"

/**
 * GameView represents the main view of the application
 * where the level is drawn.  It binds events from wxWidgets
 * and propagates them down to the Game object.
 */
class GameView : public wxWindow
{
private:
	///the game we take in
    std::unique_ptr<Game> mGame;
	///the stopwatch we run throught the program
    wxStopWatch mStopWatch;
	///the time we keep throught the game
    long mTime=0;
	///the timer we keep through the game
    wxTimer mTimer;
	///the level timer
    wxTimer mLevelTextTimer;
	///the boolean to show if were displaying level text
    bool mDisplayLevelText = true;
	///the function to start the timer
    void OnTimer(wxTimerEvent& event);
	///the current level
    int mCurrentLevel = 1;
	///checks if the song is ended
    bool mSongEnded=false;
	///the maxumum beats we have in the song
    double mMaxBeat=0;
	///checks if were playing
	bool playing = true;
	///checks if the text is done loading?
	int textDone = 0;
	///checks if the timer starts for the solo
    wxTimer mSoloIncomingTimer;
	///the timer to display go
    wxTimer mGoTimer;
	///the timer to tell us if the solo ended
    wxTimer mSoloEndedTimer;
	///the timer to show the ending message
    wxTimer mSoloEndingMessageTimer;
	///chekc if you are displaying the solo incoming
    bool mDisplaySoloIncoming = false;
	///the boolean to display go
    bool mDisplayGo = false;
	/// the boolean to display if the solo ended
    bool mDisplaySoloEnded = false;
	///the delay to start the solo
    const int mSoloDelay = 45000;
	///how many beats in a measure
    const int mBeatsInMeasure = 4;
	///the suration of the solo
    const int mSoloDuration = 27000;
	///one second delay
	const int mOneSecond = 1000;
    ///the delay in the solo ending
	const int mSoloEndingDelay = 2000;

public:
    void OnSoloIncomingTimer(wxTimerEvent& event);
    void OnGoTimer(wxTimerEvent& event);
    void OnSoloEndedTimer(wxTimerEvent& event);
    void OnSoloEndingMessageTimer(wxTimerEvent& event);
    void OnLevelTextTimer(wxTimerEvent& event);
    void Initialize(wxFrame* parent);
    void OnPaint(wxPaintEvent &event);
    void OnLeftDown(wxMouseEvent &event);
    void OnKeyDown(wxKeyEvent &event);
    void OnKeyUp(wxKeyEvent &event);
    /**
     * Update time in game
     */
    void UpdateTime();
    void OnLoadLevel0(wxCommandEvent& event);
    void OnLoadLevel1(wxCommandEvent& event);
    void OnLoadLevel2(wxCommandEvent& event);
    void OnLoadLevel3(wxCommandEvent& event);

    /**
    * Stop the timer so the window can close
    */
    void Stop() {mTimer.Stop();}
    void OnAutoPlay(wxCommandEvent &event);
};

#endif //SPARTANHERO_SPARTANHEROLIB_GAMEVIEW_H
