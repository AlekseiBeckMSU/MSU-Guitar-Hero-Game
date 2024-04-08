/**
 * @file Soundboard.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "Soundboard.h"
#include "Level.h"
#include <wx/graphics.h>

using namespace std;

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
/// Default Beat size
const double DefaultSizeBeats = 1;
/// Default Image directory
const wstring DefaultImageDir = L"images";

Soundboard::Soundboard(Level *level) : Item(level)
{
    mOwnerLevel=level;
}

void Soundboard::XmlDeclarationLoad(wxXmlNode *node)
{
    // Call up to parent class
    Declaration::XmlDeclarationLoad(node);

    // Try to load the beat size
    auto sizeBeats = node->GetAttribute(L"size-beats");
    if(!sizeBeats.ToDouble(&mSizeBeats))
    {
        mSizeBeats = DefaultSizeBeats;
    }

    // Try to load the cover image
    auto coverImageFile = node->GetAttribute(L"cover");
    mCoverImage = make_unique<wxImage>(DefaultImageDir + L"/" + coverImageFile);
    if (mCoverImage != nullptr)
    {
        mCoverBitmap = make_unique<wxBitmap>(*mCoverImage);
    }

    // Try to load the top width,
    // fall back to the cover image size if unable
    auto topWidth = node->GetAttribute(L"top-width");
    if(!topWidth.ToDouble(&mTopWidth))
    {
        if (mCoverImage != nullptr)
            mTopWidth = mCoverImage->GetWidth();
        else
            mTopWidth = 0;
    }
}

void Soundboard::Draw(wxGraphicsContext *graphics, double beat)
{
    Item::Draw(graphics, beat);
    mLevel->SetBeat(beat);

    // loops through track and call draw on each track
    for( auto track : mTracks)
    {
        track->Draw(graphics, beat);
    }

    // draw the black box
    graphics->DrawBitmap(*mCoverBitmap,
                         GetX() - GetWidth()/2,
                         GetY() - GetHeight()/2,
                         GetWidth(),
                         GetHeight());

}

void Soundboard::XmlItemLoad(wxXmlNode *node)
{
    Item::XmlItemLoad(node);

    // Check if the soundboard node has child elements.
    wxXmlNode* child = node->GetChildren();

    while(child != nullptr)
    {
        if (child->GetName() == L"track")
        {

            auto track = std::make_shared<Track>(this, mLevel);
            double trackNum;

            // Fetch attributes from XML node
            std::wstring keyImage = child->GetAttribute(L"key-image").ToStdWstring();
            std::wstring keySize = child->GetAttribute(L"key-size").ToStdWstring();
            std::wstring keyAttr = child->GetAttribute(L"key").ToStdWstring();
            child->GetAttribute(L"track").ToDouble(&trackNum);

            // Convert the first character of the key string to wchar_t, if it's not empty.
            wchar_t key = !keyAttr.empty() ? keyAttr[0] : L'\0';

            // Now LoadTrackXml
            track->LoadTrackXml(keyImage, keySize, key, trackNum);

            // Add the trackInfo to the soundboard
            this->AddTrack(track);
        }
        child = child->GetNext();
    }
}

/**
 * Add a timing to the appropriate track
 * @param timing The timing to add
 */
void Soundboard::AddTiming(std::shared_ptr<NoteTiming> timing)
{
    for (auto track : mTracks)
    {
        if(track->GetTrackNum() == timing->GetTrackNum())
        {
            track->AddTiming(timing);
            return;
        }
    }
}

void Soundboard::KeyDown(wchar_t key, double beat)
{
    // Skip if we are autoplaying
    if (mLevel->GetAutoPlay())
    {
        return;
    }

    for (auto track : mTracks)
    {
        if(track->GetKey() == key)
        {
            track->KeyDown(beat);
            return;
        }
    }
}

void Soundboard::KeyUp(wchar_t key, double beat)
{
    // Skip if we are autoplaying
    if (mLevel->GetAutoPlay())
    {
        return;
    }

    for (auto track : mTracks)
    {
        if(track->GetKey() == key)
        {
            track->KeyUp(beat);
        }
    }
}