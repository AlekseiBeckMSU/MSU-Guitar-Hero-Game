/**
 * @file Scoreboard.h
 * @author Alex Beck
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_SCOREBOARD_H
#define SPARTANHERO_SPARTANHEROLIB_SCOREBOARD_H

#include "Declaration.h"
#include "Item.h"
#include <wx/stopwatch.h>

class Score;
/**
 * the scoreboard to keep track of our score
 */
class Scoreboard : public Item
{
private:
	/// Size to display "Get Ready" before the level begins
	const int mReadySize = 20;

	/// Y location to display "Get Ready" relative to the
	/// vertical center of the scoreboard. The X value is
	/// chosen that centers the text
	const int mReadyY = -10;

	/// Font size for the measure and beat indicator
	const int mBeatSize = 35;

	/// Y location to display the measure and beat
	/// relative to the vertical center of the scoreboard.
	const int mBeatsY = -25;

	/// Font size to use to display the score
	const int mScoreSize = 30;

	/// Y location to display the score
	/// relative to the vertical center of the scoreboard.
	const int mScoreY = 15;

	/// Score we get when we successfully hit a note
	const int mGoodSoundScore = 10;

	/// The maximum bonus we can get for
	/// holding for the duration for a long sound
	const int mMaxDurationBonus = 10;

    /// The amount of beats per measure
    const int mBeatPerMeasure = 4;

    /// The current measure the level is at
    int mCurrentMeasure;
    /// The current beat the level is at
    int mCurrentBeat;
    /// The current beat integer
    int mBeat;
    /// The image to display scoreboard
    std::shared_ptr<wxImage> mScoreboardImage;
    /// The bitmap to display scoreboard
    std::shared_ptr<wxBitmap> mScoreboardBitmap;
    void DrawText(wxGraphicsContext *graphics, std::wstring str, double x, double y);
public:
    /// Scoreboard object
    Scoreboard(Level *level);

    /**
     *
     * @param visitor
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitScoreboard(this); }

    void Draw(wxGraphicsContext *graphics, double beat) override;

};

#endif //SPARTANHERO_SPARTANHEROLIB_SCOREBOARD_H
