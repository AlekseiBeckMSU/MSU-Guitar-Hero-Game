/**
 * @file Note.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_NOTE_H
#define SPARTANHERO_SPARTANHEROLIB_NOTE_H

#include "Item.h"
#include "Declaration.h"

/**
 * Note item for use in level
 */
class Note : public Declaration
{
private:

    /// The tolerance for the user hitting the note
    double mTolerance = 0;

    /// The name of the track this note belongs to
    double mTrack;

    /// The image to display the puck
    std::shared_ptr<wxImage> mPuckImage;
    /// The bitmap to display  the puck
    std::shared_ptr<wxBitmap> mPuckBitmap;

public:

    Note(Level *level);
    Note() = delete;
    void operator=(const Note &) = delete;
    Note(const Note &) = delete;

    void XmlDeclarationLoad(wxXmlNode *node) override;
    /**
     * Getter for puckbitmap
     * @return
     */
    std::shared_ptr<wxBitmap> GetPuckBitmap(){return mPuckBitmap;}
    /**
     * Get the tolerance (in beats) for this note
     * @return The tolerance (in beats)
     */
    double GetTolerance() { return mTolerance; }

    /**
     *
     * @param visitor
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitNote(this); }

    /**
     * Get the name of the track
     * @return The name of the track for this note declaration
     */
    double GetTrackNum() { return mTrack; }
};

#endif //SPARTANHERO_SPARTANHEROLIB_NOTE_H
