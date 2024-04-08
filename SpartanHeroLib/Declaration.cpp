/**
 * @file Declaration.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "Declaration.h"
#include <wx/graphics.h>

using namespace std;

/// Image directory string
const wstring DefaultImageDir = L"images";

/**
 * Constructor
 * @param level
 */
Declaration::Declaration(Level *level) : mLevel(level)
{
}

/**
 * Destructor
 */
Declaration::~Declaration()
{
}

/**
 * Load basic item data from a xml
 * node under the declarations element
 * @param node The XML node representing this item
 */
void Declaration::XmlDeclarationLoad(wxXmlNode *node)
{
    // Get the ID of this item
    mID = node->GetAttribute(L"id");
    auto imageFile = node->GetAttribute(L"image");

    // Get virtual size of the item
    auto size = node->GetAttribute(L"size");
    auto sizeArr = wxSplit(size, ',');
    if (sizeArr.size() > 1)
    {
        sizeArr[0].ToDouble(&mWidth);
        sizeArr[1].ToDouble(&mHeight);
    }

    // Get the image for this item
    mItemImage = make_unique<wxImage>(DefaultImageDir + L"/" + imageFile, wxBITMAP_TYPE_ANY);
    if (mItemImage != nullptr)
    {
        mItemBitmap = make_unique<wxBitmap>(*mItemImage);
    }
}

/**
 * Draw the image of the declaration at the specified coordinates
 * @param graphics The graphics context to draw on
 * @param x The x position to draw the image (center)
 * @param y The y position to draw the image (center)
 */
void Declaration::Draw(wxGraphicsContext* graphics, double x, double y)
{
    graphics->DrawBitmap(*mItemBitmap,
                   x - mWidth / 2,
                   y - mHeight / 2,
                   mWidth,
                   mHeight);
}
