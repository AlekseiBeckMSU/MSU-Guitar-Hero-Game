/**
 * @file Score.h
 * @author Alex Beck
 *
 *
 */



#ifndef SPARTANHERO_SPARTANHEROLIB_SCORE_H
#define SPARTANHERO_SPARTANHEROLIB_SCORE_H

#include "Item.h"

/**
 * Score class that handles the users score and gives is used by scoreboard
 */
class Score
{
private:
    /// The current level score
    int mScore = 0;
    /// The number of notes the player *should* have played
    int mNotesPassed = 0;
    /// The number of correct notes the player has hit
    int mNotesPlayed = 0;
    /// The number of misses the player has hit
    int mWhiffs = 0;
    /// The bool that determines if the solo is set for the current level
	bool mSolo = false;

public:

    /**
     * Constructor
     */
    Score() : mNotesPassed(0), mNotesPlayed(0), mWhiffs(0) {}

    void AddScore(int score);

    /**
     * Get the player's score
     * @return mScore the current score
     */
    int GetScore() { return mScore; }

    /**
     * Adds 1 to the amount of notes passed
     */
    void AddNotePass() { mNotesPassed++; }

    /**
     * Adds 1 to the amount of notes played
     */
    void AddNotePlay() { mNotesPlayed++; }

    /**
     * Adds 1 to the amount of notes whiffed
     */
    void AddWhiff() { mWhiffs++; }


    double Accuracy();

    void Reset();

	void SoloSwitch(bool soloTime);
};

#endif //SPARTANHERO_SPARTANHEROLIB_SCORE_H
