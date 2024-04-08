/**
 * @file NoteTiming.h
 * @author Alex Beck
 *
 * Header for NoteTiming class
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_NOTETIMING_H
#define SPARTANHERO_SPARTANHEROLIB_NOTETIMING_H

#include <memory>

#include "Note.h"
#include "Sound.h"
#include "Music.h"

class Track;
class Soundboard;

/**
 * NoteTiming represents a combination of note, sound, and time
 * which should be displayed by the soundboard
 */
class NoteTiming
{
private:
    /// The note for this timing
    std::shared_ptr<Note> mNote;
    /// The sound for this timing
    std::shared_ptr<Sound> mSound;
    /// The downbeat for this timing
    double mDownbeat;
	/// when we start playing the music
    double mPlayedAt = -1;
	/// the duration we start with
    double mDuration;
	/// the height of the puck
    wxDouble mPuckHeight=20;
	/// the width of the puck
    wxDouble mPuckWidth=20;
public:
    NoteTiming(std::shared_ptr<Note> note, std::shared_ptr<Sound> sound);
    NoteTiming() = delete;
    void operator=(const NoteTiming &) = delete;
    NoteTiming(const NoteTiming &) = delete;
    /// For resizing Puck
    void IncPuckDimensions();
	///the puck dimentions
    void ResPuckDimensions();

    void XmlLoad(wxXmlNode *node, Music *music);

    /**
     * Get the downbeat for this timing
     * @return The downbeat (in beats)
     */
    double GetDownbeat() { return mDownbeat; }

    /**
     * Get the track number that this timing is for
     * @return The track number for this timing
     */
    double GetTrackNum() { return mNote->GetTrackNum(); }

    /**
     * Get the beat this timing ends on
     * @return the downbeat and duration
     */
    double GetEndbeat() { return mDownbeat + mDuration; }

    /**
     * Get the duration of this timing
     * @return The duration in beats
     */
    double GetDuration() {return mDuration;}

    /**
     * The tolerance of this timing
     * @return the tolerance of this timing (beats)
     */
    double GetTolerance() { return mNote->GetTolerance(); }

    /**
     * Returns true if this timing is linked to a loop
     * @return the sound that we loop
     */
    bool IsLoop() { return mSound->GetLoop(); }

    /**
     * Returns true if this timing is playing
     * @return if the sound is playing
     */
    bool IsPlaying() {return mSound->Playing();}
	/**
	 * get if it plays or not
	 * @return where its played at
	 */
    double GetPlayedAt() { return mPlayedAt; }

    void Draw(wxGraphicsContext* graphics, Track *track, Soundboard *soundboard, double beat);
    bool Hit(double beat);
    void Play(double beat);
    void Stop();
    void Pause();
};

#endif //SPARTANHERO_SPARTANHEROLIB_NOTETIMING_H
