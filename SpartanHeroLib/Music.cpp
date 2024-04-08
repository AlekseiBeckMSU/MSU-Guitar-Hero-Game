/**
 * @file Music.cpp
 * @author Alex Beck
 *
 * Implementation for Music class, which
 * provides common utility functions for
 * time conversion within the context of the
 * current song/backing track.
 */

#include "pch.h"
#include "Music.h"

/**
 * Load the music data from xml
 * @param node The music node to load the data from
 */
void Music::XmlLoad(wxXmlNode *node)
{
	node->GetAttribute(L"beats-per-minute").ToDouble(&mBeatPerMin);
    node->GetAttribute(L"beats-per-measure").ToDouble(&mBeatPerMeasure);
	node->GetAttribute(L"measures").ToDouble(&mMeasures);
    mBacking = node->GetAttribute(L"backing");
}

/**
 * Convert beats to seconds
 * @param beats The number of beats
 * @return The number of seconds this number of beats represents
 */
double Music::BeatsToSeconds(double beats)
{
    return beats * 60.0 / mBeatPerMin;
}

/**
 * Convert seconds to beats
 * @param seconds The number of seonds
 * @return The number of beats this many seconds represents
 */
double Music::SecondsToBeats(double seconds)
{
    return seconds * mBeatPerMin / 60.0;
}

/**
 * Convert measures to beats
 * @param measures The number of measures
 * @return The total count of the beats across this number of measures
 */
double Music::MeasuresToBeats(double measures)
{
    return measures * mBeatPerMeasure;
}

/**
 * Convert measures to seconds
 * @param measures The number of measures
 * @return The total number of seconds this many measures represents
 */
double Music::MeasuresToSeconds(double measures)
{
    return BeatsToSeconds(MeasuresToBeats(measures));
}
