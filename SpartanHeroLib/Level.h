/**
 * @file Level.h
 * @author Alex Beck
 *
 * Individual level made from xml file
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_LEVEL_H
#define SPARTANHERO_SPARTANHEROLIB_LEVEL_H

#include "DeclarationVisitor.h"
#include "Item.h"
#include "Note.h"
#include "Sound.h"
#include "Score.h"
#include "Declaration.h"
#include "Soundboard.h"
#include "Scoreboard.h"
#include "Music.h"
#include <vector>
#include <memory>

/**
 * Individual level made from xml file
 */
class Level
{
private:
    /// Countdown value
    double mCountDownBeat = 8;

    std::vector <std::shared_ptr<Declaration>> mDeclarations; ///< Declaration items in level
    std::vector <std::shared_ptr<Note>> mNotes; ///< Notes in level
    std::vector <std::shared_ptr<Sound>> mSounds; ///< Sounds in the level
    /// The width of the level in virtual pixels
    double mWidth;
    /// The height of the level in virtual pixels
    double mHeight;
    /// Key state
    bool mKeyDown;
    /// Pointer to Score class
    std::shared_ptr<Score> mScore;

    /// Beat value
    int mBeat=0;
    /// Key code
    wxChar mKeyCode;
    /// Auto play state
    bool mAutoPlay = false;
    /// Music Data
    Music mMusicData;
    /// audio engine
    ma_engine *mAudioEngine;

    void XmlAudio(wxXmlNode *node);

    void XmlDeclarations(wxXmlNode *node);

    void XmlItems(wxXmlNode *node);

    void XmlMusic(wxXmlNode *node);

    /// Playing state
    bool mPlaying = false;

public:

	/**
	 * gets the current beat
	 * @return the current beat
	 */
    int GetCurrentBeat(){return mBeat;}

    std::shared_ptr<Sound> GetSound(std::wstring id);

    std::shared_ptr<Note> GetNote(std::wstring id);

    /**
     * Constructor
     * @param audio
     */
    Level(ma_engine *audio);

    void operator=(const Level &) = delete;
    Level(const Level &) = delete;
    Level() = default;

    /**
     * Clear function
     */
    void Clear();

    /**
     * Sets up audio
     */
    void SetAutoPlay();

	/**
	 * sets the auto play
	 * @return the bool to say if we are autoplaying
	 */
    bool GetAutoPlay() { return mAutoPlay; }

    void Load(const std::wstring &fileName);

	/**
	 * gets the key state and return it
	 * @return the curren key state
	 */
    bool GetKeyState() { return mKeyDown; }

    /**
     * Get the loaded width of the level in virtual pixels
     * @return
     */
    double GetWidth() { return mWidth; }

    /**
     * Get the loaded height of the level in virtual pixels
     * @return
     */
    double GetHeight() { return mHeight; }

	/**
	 * gets the score and returns it
	 * @return the current score
	 */
    std::shared_ptr<Score> GetScore() { return mScore; }

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);

    void Accept(DeclarationVisitor *visitor);

    /**
     *
     * @param key
     */
    void OnKeyPress(wxChar key);

    /**
     *
     * @param key
     */
    void OnKeyRelease(wxChar key);

	/**
	 * gets the key code and retuens the key
	 * @return the current key
	 */
    wchar_t GetKeyCode() { return mKeyCode; }

	/**
	 * gets the music to return
	 * @return the music playing
	 */
    Music *GetMusic () { return &mMusicData; }

    void Update(double deltaTime);

	/**
	 * plays the song and sets playing to true
	 */
	void Play() { mPlaying = true; }

    /**
     * Getter to get playing state
     * @return
     */
    bool IsPlaying() { return mPlaying; }

    void SetBeat(double beat);
};

#endif //SPARTANHERO_SPARTANHEROLIB_LEVEL_H
