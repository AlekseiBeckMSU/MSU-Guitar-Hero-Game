/**
 * @file Sound.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_SOUND_H
#define SPARTANHERO_SPARTANHEROLIB_SOUND_H

#include <miniaudio.h>
#include <memory>

/**
 * Represents a sound which can be played by the program
 */
class Sound
{
private:
    /// The miniaudio sound
    ma_sound mSound;

    /// The name of the sound
    std::wstring mName;

    /// Has the sound loaded?
    bool mLoaded = false;

    /// Weather the sound is a loop or not
    bool mLoop = false;
public:

    bool Playing();
    void Play();
    void Pause();
    void Stop();

    float GetElapsed();
    float GetLength();

    /**
     * Getter to get name
     * @return
     */
    std::wstring GetName() { return mName; }
    /**
     * Get loop state
     * @return
     */
    bool GetLoop() { return mLoop; }
    void XmlLoad(wxXmlNode *node, ma_engine *engine);

    ~Sound();
};

#endif //SPARTANHERO_SPARTANHEROLIB_SOUND_H
