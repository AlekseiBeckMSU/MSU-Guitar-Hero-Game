/**
 * @file Sound.cpp
 * @author Alex Beck
 *
 * Implementation details for Sound class
 */

#include "pch.h"
#include "Sound.h"

using namespace std;

/// The relative directory we will load audio files from
const wstring AudioDirectory = L"audio";
/// The default volume for a sound file if one is not provided
const double DefaultVolume = 0.5;

/**
 * Destructor
 */
Sound::~Sound()
{
    if (mLoaded)
    {
        if (ma_sound_is_playing(&mSound))
        {
            ma_sound_stop(&mSound);
        }

        ma_sound_uninit(&mSound);
    }
}

/**
 * Returns weather the sound is playing
 * @return true if the sound is playing, false otherwise
 */
bool Sound::Playing()
{
    if (mLoaded)
    {
        return ma_sound_is_playing(&mSound);
    }
    return false;
}

/**
 * Resumes playing the sound if paused, but plays from the beginning
 * if the sound is at the end or is already playing.
 */
void Sound::Play()
{
    // Guard for if the sound is not loaded
    if (!mLoaded)
        return;

    // If the sound was already playing: stop,
    // reset, and replay.
    if (ma_sound_is_playing(&mSound))
    {
        ma_sound_stop(&mSound);
        ma_sound_seek_to_pcm_frame(&mSound, 0);
    }

    // If the sound was at the end: reset and replay.
    if (mSound.atEnd)
        ma_sound_seek_to_pcm_frame(&mSound, 0);

    // Play the sound
    ma_sound_start(&mSound);
}

/**
 * Pause the sound (can resume with Play)
 */
void Sound::Pause()
{
    if (mLoaded)
    {
        ma_sound_stop(&mSound);
    }
}

/**
* Stop the sound (plays back from beginning if Play is invoked afterward)
*/
void Sound::Stop()
{
    if (!mLoaded)
        return;

    // Stop the sound
    if (ma_sound_is_playing(&mSound))
        ma_sound_stop(&mSound);

    // Reset the sound
    ma_sound_seek_to_pcm_frame(&mSound, 0);
}

/**
 * Gets the cursor time of the sound, or -1 if there was an error.
 * @return The difference between the start of the sound file and where the sound is currently playing from (in seconds)
 */
float Sound::GetElapsed()
{
    if (!mLoaded)
        return -1;

    // Get sound time
    float out;
    auto result = ma_sound_get_cursor_in_seconds(&mSound, &out);

    // Error value
    if (result != MA_SUCCESS)
        out = -1;

    return out;
}

/**
 * Gets the length (in seconds) of the sound
 * @return The length of the sound in seconds (or -1 if there was an error)
 */
float Sound::GetLength()
{
    if (!mLoaded)
        return -1;

    // Get length
    float out;
    auto result = ma_sound_get_length_in_seconds(&mSound, &out);

    if (result != MA_SUCCESS)
        out = -1;

    return out;
}

 /**
  * Load the sound file from an xml node
  * @param node The xml node that represents this sound
  * @param engine audio engine
  */
void Sound::XmlLoad(wxXmlNode *node, ma_engine *engine)
{
    if (engine != nullptr)
    {
        // Get the file name from the node
        auto fileName = node->GetAttribute(L"audio");
        // Check weather we should loop the sound based on weather the node is long
        mLoop = node->GetAttribute(L"long") == L"true";
        // Load the name of this sound
        mName = node->GetAttribute(L"name");

        // Try to load the audio file
        auto audioFile = AudioDirectory + L"/" + fileName;
        auto result = ma_sound_init_from_file_w(engine, audioFile.c_str(), 0, NULL, NULL, &mSound);

        if (result != MA_SUCCESS)
        {
            // If we can't load the sound, show an error
            wxString msg;
            msg.Printf(L"Unable to load audio file %s - %d", audioFile, result);
            wxMessageBox(msg, wxT("miniaudio failure"), wxICON_ERROR);
        }
        else
        {
            // Otherwise indicate that we loaded the sound
            mLoaded = true;
            ma_sound_set_looping(&mSound, mLoop);

            // Get volume, set default if no volume is defined.
            double volume;
            if (!node->GetAttribute("volume").ToDouble(&volume))
                volume = DefaultVolume;

            // Set volume
            ma_sound_set_volume(&mSound, (float) volume);
        }
    }
}