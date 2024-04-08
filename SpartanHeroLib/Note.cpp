/**
 * @file Note.cpp
 * @author Alex Beck
 */

#include "pch.h"

#include "Note.h"

/// Default tolerance for notes if one is not provided
const double DefaultTolerance = 0.5;

/// Default track for notes if one is not provided
const double DefaultTrack = 1;

/// Image directory string
const std::wstring DefaultImageDir = L"images";

/**
 * Constructor
 * @param level The level this declaration belongs to
 */
Note::Note(Level *level) : Declaration(level)
{
}

/**
 * Load note info
 * @param node
 */
void Note::XmlDeclarationLoad(wxXmlNode *node)
{
    Declaration::XmlDeclarationLoad(node);

    auto track = node->GetAttribute(L"track");
    if (!track.ToDouble(&mTrack))
    {
        mTrack = DefaultTrack;
    }

    auto tolerance = node->GetAttribute(L"tolerance");
    if (!tolerance.ToDouble(&mTolerance))
    {
        mTolerance = DefaultTolerance;
    }
    auto image = node->GetAttribute(L"image");
    mPuckImage = std::make_unique<wxImage>(DefaultImageDir + L"/" + image);
    if (mPuckImage != nullptr)
    {
        mPuckBitmap=std::make_unique<wxBitmap>(*mPuckImage);
    }
}
