/**
 * @file Game.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_GAME_H
#define SPARTANHERO_SPARTANHEROLIB_GAME_H

#include "Level.h"
#include <memory>

/**
 * Game represents the game system
 */
class Game
{
private:
    /// The currently loaded level
    std::shared_ptr<Level> mCurrentLevel;
    /// The audio engine to use
    ma_engine mEngine;
    /// The relative scale from real pixels to virtual pixels
    double mScale;
    /// The X offset of the virtual screen
    double mXOffset;
    /// The Y offset of the virtual screen
    double mYOffset;
    /// Weather the audio engine could be started
    bool mAudioLoaded = false;

public:
    Game(std::wstring level);
    ~Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void OnLeftDown(int x, int y);
    void OnKeyUp(wxChar I);
    void OnKeyDown(wxChar I);
    void LoadLevel(std::wstring levelFile);
    void Update(double elapsed);

	void Play();
    void SetAutoPlay();

	/**
	 * the funciton to switch levels
	 * @param b the level to switch to
	 */
	void SoloSwitch(bool b){mCurrentLevel->GetScore()->SoloSwitch(b);}

    /**
     * Getter to return current level
     * @return
     */
    std::shared_ptr<Level>GetLevel(){return mCurrentLevel;}
};

#endif //SPARTANHERO_SPARTANHEROLIB_GAME_H
