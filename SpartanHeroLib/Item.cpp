/**
 * @file Item.cpp
 * @author Alex Beck
 */

#include "pch.h"

#include "Item.h"
#include <wx/graphics.h>

using namespace std;

/**
 * Load extra item parameters from a xml
 * node under the item element
 * @param node The XML node representing this item
 */
void Item::XmlItemLoad(wxXmlNode *node)
{
    // Get virtual position for this item
    auto size = node->GetAttribute(L"p");
    auto sizeArr = wxSplit(size, ',');
    if (sizeArr.size() > 1)
    {
        sizeArr[0].ToDouble(&mX);
        sizeArr[1].ToDouble(&mY);
    }
}

/**
 * draws the items in play x,y
 * @param graphics the graphics we use to draw
 * @param beat the beat to draw it to
 */
void Item::Draw(wxGraphicsContext *graphics, double beat)
{
    Declaration::Draw(graphics, mX, mY);
}

/**
 * Accept a visitor for this item
 * @param visitor
 */
void Item::Accept(DeclarationVisitor *visitor)
{
    visitor->VisitItem(this);
}