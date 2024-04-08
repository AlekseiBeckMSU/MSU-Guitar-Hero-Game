/**
 * @file Soundboard.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_SOUNDBOARD_H
#define SPARTANHERO_SPARTANHEROLIB_SOUNDBOARD_H

#include "Sound.h"
#include "Item.h"
#include "Declaration.h"
#include "NoteTiming.h"
#include "Track.h"

/**
 * Soundboard represents the playing area of the game,
 * with tracks and notes which move towards the key images.
 */
class Soundboard : public Item
{
private:

    /// The sounds that notes may play
    std::vector <std::shared_ptr<Track>> mTracks;
    /// Bool determines if song was ended
    bool mSongEnded;

    /// The number of total beats to show on the soundboard
    double mSizeBeats = 0;

    /// The top width of the soundboard
    double mTopWidth = 0;

    /// The image to display as the cover for the top of the soundboard
    std::shared_ptr<wxImage> mCoverImage;
    /// The bitmap to display as the cover for the soundboard
    std::shared_ptr<wxBitmap> mCoverBitmap;
    /// level object
    Level * mOwnerLevel;

public:
    /**
     * Constructor
     * @param level
     */
    Soundboard(Level *level);

    /**
     * Loads Xml from a node
     * @param node
     */
    void XmlDeclarationLoad(wxXmlNode *node) override;

    /**
     * Returns the current level object
     * @return mOwnerLevel
     */
    Level * GetLevel(){return mOwnerLevel;}
    /**
     *
     * @param visitor
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitSoundboard(this); }

    /**
     * Draws the soundboard in the view window
     * @param graphics
     * @param beat
     */
    void Draw(wxGraphicsContext *graphics, double beat) override;

    void AddTiming(std::shared_ptr<NoteTiming> timing);

    /**
     * Adds a track to the current tracks
     * @param track
     */
    void AddTrack(std::shared_ptr<Track> track) {
        mTracks.push_back(track);
    }

    /**
     * loads an Xml item
     * @param node
     */
    void XmlItemLoad(wxXmlNode *node) override;

    /**
     * returns the top width of the soundboard
     * @return
     */
    double GetTopWidth(){return mTopWidth;}

    /**
     * Getter for the current tracks
     * @return
     */
    std::vector<std::shared_ptr<Track>> GetTracks() const{return mTracks;}

    /**
     * Get the number of beats (ahead) that each track should show
     * @return
     */
    double GetSizeBeats() {return mSizeBeats;}

    /**
     * Tracks if the key is currently down
     * @param key
     * @param beat
     */
    void KeyDown(wchar_t key, double beat);

    /**
     * Tracks if the key is currently up
     * @param key
     * @param beat
     */
    void KeyUp(wchar_t key, double beat);
};

#endif //SPARTANHERO_SPARTANHEROLIB_SOUNDBOARD_H
