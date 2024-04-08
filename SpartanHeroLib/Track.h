/**
 * @file Track.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_TRACK_H
#define SPARTANHERO_SPARTANHEROLIB_TRACK_H

#include "Sound.h"
#include "Declaration.h"
#include "NoteTiming.h"
#include "Item.h"

class Soundboard;
class Level;

/**
 * represents the track that the buttons go down
 */
class Track
{
private:

	/// soundboard to save and use
    Soundboard * mSoundboard;
	///the level we use throughout
    Level * mLevel;


    /// The track number
    double mTrackNum;

    /// The key that the track represents
    wchar_t mKey;

	/// The item image
	std::shared_ptr<wxImage> mKeyImage;

    /// The item bitmap
    std::shared_ptr<wxBitmap> mKeyBitmap;


	///tells us if the key is being pressed
    bool mKeyPress;
    /// The width of the key image (virtual pixels)
    double mKeyWidth;
    /// The height of the key image (virtual pixels)
    double mKeyHeight;

    /// All the note timings for this track
    std::vector <std::shared_ptr<NoteTiming>> mTimings;
	///the next timing comparativly
    int mNextTiming = 0;

    /// The currently pressed down timing
    std::shared_ptr<NoteTiming> mHeldTiming;
	/**
	 * the next timing
	 * @param beat the beat we go to
	 * @return the next beat
	 */
    int GetNextTiming(double beat);
public:

    /**
     * constructor
     * @param soundboard the soundboard element we pass
     * @param level the level we use and write to
     */
	Track(Soundboard* soundboard, Level *level) : mSoundboard (soundboard), mLevel(level) {}

	/**
	 * the load to load from the xml
	 * @param node the node we pass
	 */
	void XmlLoad(wxXmlNode *node);

	/**
	 * gets the bitmap of the key and returns it
	 * @return the bitmap of the key
	 */
    std::shared_ptr<wxBitmap> GetKeyBitmap(){return mKeyBitmap;}

    void Draw(wxGraphicsContext *graphics, double beat);

    void LoadTrackXml(const std::wstring& image, const std::wstring& size, const wchar_t& key, const double& tracknum);

	/**
	 * gets the key and returns it
	 * @return the key on the track
	 */
    wchar_t GetKey() const {return mKey;}

	/**
	 * the track number we write to
	 * @return the track number
	 */
    double GetTrackNum() const {return mTrackNum;}

    double GetX1();
    double GetY1();
    double GetX2();
    double GetY2();

    void AddTiming(std::shared_ptr<NoteTiming> timing);

	/**
	 * gets the valid key press
	 * @param query the character thats pressed to see if it valid
	 */
    void ValidKeypress(wchar_t query);

    void KeyDown(double beat);
    void KeyUp(double beat);
};

#endif //SPARTANHERO_SPARTANHEROLIB_TRACK_H
