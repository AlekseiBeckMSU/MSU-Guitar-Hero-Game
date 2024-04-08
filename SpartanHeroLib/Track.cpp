/**
 * @file Track.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "Track.h"
#include <string>
#include <wx/graphics.h>
#include "Soundboard.h"
#include "Level.h"

using namespace std;

/// Width of the track line. The line is
/// drawn a wxBLACK.
const int TrackLineWidth = 5;

/// Width of the long duration lines. These
/// lines are drawn as wxRED
const int LongDurationLineWidth = 12;

/// The maximum number of tracks
const int MaxTracks = 10;

/// What is the border of the left and right
/// of the tracks? This is the percentage of
/// the space to the left of the first track line
/// and to the right of the last track line
const double Border = 0.075;

/// Top clearance so we don't draw past the cover
/// as a fraction of the soundboard height. This
/// is where the pucks come in
const double TopClearance = 0.1;

/// Percentage down on the soundboard to the keys
/// This is where the pucks go under the key and
/// disappear.
const double KeyRow = 0.85;

/**
 * Get the x coordinate of the top of the line
 * @return The x coordinate in virtual pixels
 */
double Track::GetX1()
{
    double topWidth = mSoundboard->GetTopWidth();
    double x1 = mSoundboard->GetX() - topWidth / 2;
    x1 += topWidth * (mTrackNum - 0.5) / MaxTracks;
    return x1;
}

/**
 * Get the x coordinate of the bottom of the line
 * @return The x coordinate in virtual pixels
 */
double Track::GetX2()
{
    double botWidth = mSoundboard->GetWidth() * (1 - 2*Border);
    double x2 = mSoundboard->GetX() - botWidth / 2;
    x2 += botWidth * (mTrackNum - 0.5) / MaxTracks;
    return x2;
}

/**
 * Get the y coordinate of the top of the line
 * @return The y coordinate in virtual pixels
 */
double Track::GetY1()
{
    return mSoundboard->GetY() - mSoundboard->GetHeight()/2 * (1 - TopClearance);
}

/**
 * Get the y coordinate of the bottom of the line
 * @return The y coordinate in virtual pixels
 */
double Track::GetY2()
{
    return mSoundboard->GetY() + mSoundboard->GetHeight()/2 - ((1-KeyRow) * mSoundboard->GetHeight());
}

int Track::GetNextTiming(double beat)
{
    while (mNextTiming < mTimings.size())
    {
        auto timing = mTimings[mNextTiming];
        if (timing->GetEndbeat() > beat)
            break;
        mNextTiming++;
    }
    return mNextTiming;
}
/**
 * draws the tracks and the pucks
 * @param graphics the graphics we use to draw
 * @param beat the beat count to move notes
 */
void Track::Draw(wxGraphicsContext *graphics, double beat)
{
    mLevel=mSoundboard->GetLevel();

    wxPen blackPen(*wxBLACK, TrackLineWidth); // Black pen
    graphics->SetPen(blackPen);

    graphics->StrokeLine(GetX1(),
                         GetY1(),
                         GetX2(),
                         GetY2());

    int lastTiming = mNextTiming;
    // Get the first timing to draw
    int startTiming = GetNextTiming(beat);

    while (lastTiming < startTiming)
    {
        mLevel->GetScore()->AddNotePass();
        if (mTimings[lastTiming]->GetPlayedAt() >= 0)
            mLevel->GetScore()->AddNotePlay();
        lastTiming++;
    }

    // Get the beat past which we should stop drawing
    double endbeat = beat + mSoundboard->GetSizeBeats();

    // Release beat for autoplay
    if (mLevel->GetAutoPlay() && mHeldTiming != nullptr)
    {
        if (mHeldTiming->GetEndbeat() <= beat)
            KeyUp(beat);
    }

    // Loop over timings
    while (startTiming < mTimings.size())
    {
        auto timing = mTimings[startTiming];

        // Keydown note for autoplay
        if (mLevel->GetAutoPlay() && mHeldTiming == nullptr)
        {
            if (timing->Hit(beat) && timing->GetDownbeat() <= beat && timing->GetPlayedAt() < 0)
                KeyDown(beat);
        }

        // If this timing would be off the soundboard
        // then stop drawing
        if (timing->GetDownbeat() > endbeat)
            break;

        // Draw the timing
        timing->Draw(graphics, this, mSoundboard, beat);
        startTiming++;
    }

    graphics->DrawBitmap(*mKeyBitmap,
                         GetX2() - mKeyWidth / 2,
                         GetY2() - mKeyHeight / 2,
                         mKeyWidth,
                         mKeyHeight);

    // Check if we are past the end of the held note
    if (mHeldTiming != nullptr && mHeldTiming->GetEndbeat() < beat)
    {
        // If it's a loop, stop playing
        if (mHeldTiming->IsLoop() && mHeldTiming->IsPlaying())
            mHeldTiming->Stop();
    }
}
/**
 * loads the track from the xml
 * @param image image string we take in for the keys
 * @param size the size of the keys
 * @param key what key should be pushed
 * @param tracknum what track its on
 */
void Track::LoadTrackXml(const wstring& image, const wstring& size, const wchar_t& key, const double& tracknum) {
    // Splitting the size string and converting to double
    auto sizeArr = wxSplit(size, ',');
    if (sizeArr.size() > 1) {
        sizeArr[0].ToDouble(&mKeyWidth);
        sizeArr[1].ToDouble(&mKeyHeight);
    }
    mKey = key;
    mTrackNum = tracknum;

	mKeyImage = std::make_shared<wxImage>("images/" + image, wxBITMAP_TYPE_ANY);
    mKeyBitmap = std::make_shared<wxBitmap>(*mKeyImage);
}
/**
 * the timing to stay in beat
 * @param timing each not timing to know when to press or hold
 */
void Track::AddTiming(std::shared_ptr<NoteTiming> timing)
{
    auto downbeat = timing->GetDownbeat();

    if (mTimings.empty() || mTimings[mTimings.size() - 1]->GetDownbeat() < timing->GetDownbeat())
    {
        mTimings.push_back(timing);
        return;
    }

    for (auto i = mTimings.begin(); i != mTimings.end(); i++) {
        if (downbeat > i->get()->GetDownbeat())
            mTimings.insert(i, timing);
    }
}
/**
 * checks if the key is pressed on beat
 * @param beat the beat to check if the not is pressed on
 */
void Track::KeyDown(double beat)
{
    if (mHeldTiming != nullptr)
    {
        return;
    }

    // Get timing offset, and weather or not we hit a timing
    auto next = GetNextTiming(beat);
    bool hit = false;

    while (next < mTimings.size())
    {
        auto timing = mTimings[next];

        // If this timing is hit, play the note
        if ((timing->Hit(beat) && timing->GetPlayedAt() < 0))
        {
            hit = true;
            mHeldTiming = timing;
            timing->Play(beat);
            break;
        }
        // If this timing is past the current beat, we're done
        else if (timing->GetDownbeat() - timing->GetTolerance() > beat)
            break;

        next++;
    }

    if (!hit)
    {
        mLevel->GetScore()->AddWhiff();

    }

	if(hit)
	{
		mLevel->GetScore()->AddScore(10);
	}

}
/**
 * checks the key comes up or if it is a heald key
 * @param beat the beat to check if you bring it up early
 */
void Track::KeyUp(double beat)
{
    if (mHeldTiming != nullptr)
    {
        if (mHeldTiming->IsLoop())
        {
            auto heldFor = beat - mHeldTiming->GetPlayedAt();
            auto heldTrue = min(mHeldTiming->GetDuration(), heldFor);
            auto points = (int) (10 * heldTrue) / mHeldTiming->GetDuration();
            mLevel->GetScore()->AddScore((int)points);
        }

        if (mHeldTiming->IsLoop() && mHeldTiming->IsPlaying())
            mHeldTiming->Stop();
        mHeldTiming = nullptr;
    }
}

