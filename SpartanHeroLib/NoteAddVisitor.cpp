/**
 * @file NoteAddVisitor.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "NoteAddVisitor.h"
#include "Soundboard.h"

using namespace std;

/**
 * Constructor
 * @param timing The timing we will add to the soundboard
 */
NoteAddVisitor::NoteAddVisitor(shared_ptr<NoteTiming> timing) : mTiming(timing)
{}

/**
 * Visit a soundboard and add the timing to it
 * @param soundboard The soundboard to visit
 */
void NoteAddVisitor::VisitSoundboard(Soundboard *soundboard)
{
    soundboard->AddTiming(mTiming);
}