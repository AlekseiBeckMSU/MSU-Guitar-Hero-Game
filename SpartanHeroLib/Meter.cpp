/**
 * @file Meter.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "Meter.h"
#include "Level.h"
#include <wx/graphics.h>

using namespace std;

/// The default directory to look for image files
const wstring DefaultImageDir = L"images";

Meter::Meter(Level *level) : Item(level)
{
}

/**
 * Load declaration
 * @param node
 */
void Meter::XmlDeclarationLoad(wxXmlNode *node)
{
    Declaration::XmlDeclarationLoad(node);

    auto needleImageFile = node->GetAttribute(L"needle");
    mNeedleImage = make_unique<wxImage>(DefaultImageDir + L"/" + needleImageFile);
    if (mNeedleImage != nullptr)
    {
        mNeedleBitmap = make_unique<wxBitmap>(*mNeedleImage);
    }

    auto coverImageFile = node->GetAttribute(L"cover");
    mCoverImage = make_unique<wxImage>(DefaultImageDir + L"/" + coverImageFile);
    if (mCoverImage != nullptr)
    {
        mCoverBitmap = make_unique<wxBitmap>(*mCoverImage);
    }
}

/**
 * Draw declarations
 * @param graphics
 * @param beat
 */
void Meter::Draw(wxGraphicsContext *graphics, double beat)
{
    Item::Draw(graphics, beat);

    int needlePivotY = GetHeight() * mNeedlePivotYOffset;
    graphics->PushState();
    graphics->Translate(GetX(), GetY() + needlePivotY - GetHeight()/2);

    auto rotation = mLevel->GetScore()->Accuracy() * 2 * mMaxNeedleRotation;
    rotation -= mMaxNeedleRotation;

    // the angle the needle will be at when drawn
    graphics->Rotate(rotation);

    // draw the meter needle image
    graphics->DrawBitmap(*mNeedleBitmap,
                         -GetWidth()/2,
                         -needlePivotY,
                         GetWidth(),
                         GetHeight());

    graphics->PopState();

    // draw the meter cover image
    graphics->DrawBitmap(*mCoverBitmap,
                         GetX() - GetWidth()/2,
                         GetY() - GetHeight()/2,
                         GetWidth(),
                         GetHeight());
}

