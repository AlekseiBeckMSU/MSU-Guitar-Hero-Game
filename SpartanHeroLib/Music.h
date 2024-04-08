/**
 * @file Music.h
 * @author Alex Beck
 *
 * Header file for the music class
 * handles conversions between beats and seconds
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_MUSIC_H
#define SPARTANHERO_SPARTANHEROLIB_MUSIC_H

#include "Sound.h"
#include "Declaration.h"

/**
 * Music represents the game music
 */
class Music
{
private:
    /// Number of beats per minute
	double mBeatPerMin = 0;
    /// Number of beats per measure
    double mBeatPerMeasure = 0;
    /// Number of measures in the song
    double mMeasures = 0;
    /// Name of backing track
    std::wstring mBacking = L"";
public:

    void operator=(const Music &) = delete;
    Music(const Music &) = delete;

    /**
     * Constructor
     */
    Music() {}

    void XmlLoad(wxXmlNode *node);

    double BeatsToSeconds(double beats);
    double SecondsToBeats(double seconds);
    double MeasuresToSeconds(double measures);
    double MeasuresToBeats(double measures);

    /**
     * Get the sound name of the backing track
     * @return The sound name of the backing track as a wstring
     */
    std::wstring GetBacking() {return mBacking;}

    /**
     * Getter
     * @return
     */
    double GetMeasures() {return mMeasures;}

    /**
     * Getter
     * @return
     */
    double GetBeatsPerMeasure() { return mBeatPerMeasure; }

    /**
     * Getter
     * @return
     */
    double GetBeatsPerMinute() { return mBeatPerMin; }
};

#endif //SPARTANHERO_SPARTANHEROLIB_MUSIC_H
