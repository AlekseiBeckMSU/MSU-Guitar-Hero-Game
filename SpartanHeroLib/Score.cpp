/**
 * @file Score.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "Score.h"
#include "Scoreboard.h"
#include <wx/graphics.h>


/**
 * Function to return the accuracy of the player
 * @return accuracy of notes his
 */
double Score::Accuracy()
{
    if (mWhiffs + mNotesPassed == 0)
        return 1;
    double off = mWhiffs + abs(mNotesPlayed - mNotesPassed);
    return 1 - off / (double)(mNotesPassed + mWhiffs);
}

/**
 * Reset accuracy
 */
void Score::Reset()
{
    mWhiffs = 0;
    mNotesPassed = 0;
    mScore = 0;
    mNotesPlayed = 0;
}

/**
 * Adds to the mScore with score parameter
 * @param score
 */
void Score::AddScore(int score)
{
	if(mSolo)
		mScore += (score * 2);
	else
		mScore += score;
}

/**
 * Switches level to solo time
 * @param soloTime
 */
void Score::SoloSwitch(bool soloTime)
{
	mSolo = soloTime;
}