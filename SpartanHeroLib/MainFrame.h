/**
 * @file MainFrame.h
 *
 * @author Alex Beck
 *
 * top main frame for the application
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_MAINFRAME_H
#define SPARTANHERO_SPARTANHEROLIB_MAINFRAME_H

class GameView;

/**
 * top main frame for the application
 */
class MainFrame : public wxFrame
{
private:

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    /// pointer to gameview
    GameView * mGameView;

public:

    void Initialize();

    void OnClose(wxCloseEvent &event);
};

#endif //SPARTANHERO_SPARTANHEROLIB_MAINFRAME_H
