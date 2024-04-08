/**
 * @file NoteTiming.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "NoteTiming.h"
#include "Soundboard.h"
#include <wx/graphics.h>

/// Width of the long duration lines. These
/// lines are drawn as wxRED
const int LongDurationLineWidth = 12;
/// Default off set for pucks
const int OffsetForPuck = 18;

using namespace std;

 /**
 * Constructor
 * @param note The note item to draw for this timing
 * @param sound The sound to play for this timing
  */
NoteTiming::NoteTiming(std::shared_ptr<Note> note, std::shared_ptr<Sound> sound)
    : mNote(note), mSound(sound)
{
}

/**
 * Draw the note on screen for this timing
 * @param graphics The graphics context to draw this note on
 * @param track The track that this note is shown on
 * @param soundboard The soundboard that this note is shown on
 * @param beat the beat we draw to 
 */
void NoteTiming::Draw(wxGraphicsContext *graphics, Track *track, Soundboard *soundboard, double beat)
{

    // Get the start and end points for the whole track
    double dx = track->GetX2() - track->GetX1(), dy = track->GetY2() - track->GetY1();

    // The percent up from the bottom of the track to draw the note on
    double percentUp = (mDownbeat - beat) / soundboard->GetSizeBeats();

    // The percent of the length of the track to draw the note's tail on
    double percentTail = mDuration / soundboard->GetSizeBeats();

    double x1 = track->GetX2() - dx * percentUp;
    double x2 = x1 - dx * percentTail;

    double y1 = track->GetY2() - dy * percentUp;
    double y2 = y1 - dy * percentTail;

    if (y1 > track->GetY2())
    {
        // end at key bitmap
        x1 = track->GetX2();
        y1 = track->GetY2();
    }

    if (y2 < track->GetY1())
    {
        // start at top
        x2 = track->GetX1();
        y2 = track->GetY1();
    }

    wxPen redPen(*wxRED, LongDurationLineWidth); // Red pen
    graphics->SetPen(redPen);

    if (IsLoop())
        graphics->StrokeLine(x1, y1, x2, y2);

    // Calculate the percent of the size of the puck
    auto percentLow = soundboard->GetTopWidth() / soundboard->GetWidth();
    auto percentOverall = percentLow + (1 - percentLow) * (1 - percentUp);
    percentOverall = percentOverall > 1 ? 1 : percentOverall;

    // Scale down puck
    auto puckWidth = mNote->GetWidth() * percentOverall;
    auto puckHeight = mNote->GetHeight() * percentOverall;

    if (y1 < track->GetY2())
    {
        graphics->DrawBitmap(*mNote->GetPuckBitmap(),x1-puckWidth/2, y1-puckHeight/2, puckWidth, puckHeight);
    }
}

/**
 * Weather the player can currently hit the note
 * @param beat The beat that the player is trying to hit the note on
 * @return True if the player is currently able to hit this note
 */
bool NoteTiming::Hit(double beat)
{
    return beat >= mDownbeat - mNote->GetTolerance() && beat <= mDownbeat + mNote->GetTolerance();
}

/**
 * Play note
 * @param beat
 */
void NoteTiming::Play(double beat)
{
    if (mPlayedAt >= 0)
        return;
    mPlayedAt = beat;
    mSound->Play();
}
/**
 * Pause note timimg
 */
void NoteTiming::Pause()
{
    mSound->Pause();
}

/**
 * Stop playing the sound this timing is linked to
 */
void NoteTiming::Stop()
{
    mSound->Stop();
}

/**
 * loads from the xml document
 * @param node the node we take to take to get beat and measure
 * @param music the music we take to save
 */
void NoteTiming::XmlLoad(wxXmlNode *node, Music *music)
{
    // Load beat and measure
    double beat;
    double measure;
    node->GetAttribute(L"beat").ToDouble(&beat);
    node->GetAttribute(L"measure").ToDouble(&measure);

    // Get total beats until this note is played
    mDownbeat = music->MeasuresToBeats(measure - 1) + beat - 1;

    // Get duration of the note
    node->GetAttribute(L"duration").ToDouble(&mDuration);
}
