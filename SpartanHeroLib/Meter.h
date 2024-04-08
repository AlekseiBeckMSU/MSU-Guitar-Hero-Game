/**
 * @file Meter.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_METER_H
#define SPARTANHERO_SPARTANHEROLIB_METER_H

#include "Item.h"
#include "Declaration.h"
#include "NoteTiming.h"

/**
 * Meter represents the meter which shows how accurate a player has been
 */
class Meter : public Item
{
private:
    /// Positive or negative rotations of this amount will move
    /// the needle to the limit in that direction.
    /// A meter score of 0 will be a rotation of -0.9
    /// A meter score of 100% (11) will be a rotation of 0.9
    const double mMaxNeedleRotation = 0.9;

    /// Needle rotation offset
    double mNeedleRotationOffset = 0.0;

    /// This is how far down the need image the pivot point is
    /// as a percentage of the height of the image.
    const double mNeedlePivotYOffset = 0.80;

    /// Cover image
    std::shared_ptr<wxImage> mCoverImage;
    ///Cover bitmap
    std::shared_ptr<wxBitmap> mCoverBitmap;

    /// Needle image
    std::shared_ptr<wxImage> mNeedleImage;
    ///Need bitmap
    std::shared_ptr<wxBitmap> mNeedleBitmap;

    /// The note for this timing
    std::shared_ptr<NoteTiming> mBeat;

public:

    /**
     * Constructor
     * @param level
     */
    Meter(Level *level);
    void XmlDeclarationLoad(wxXmlNode *node) override;

    /**
     *
     * @param visitor
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitMeter(this); }

    void Draw(wxGraphicsContext *graphics, double beat) override;
};

#endif //SPARTANHERO_SPARTANHEROLIB_METER_H
