/**
 * @file KeyUpVisitor.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "KeyUpVisitor.h"
#include "Soundboard.h"

void KeyUpVisitor::VisitSoundboard(Soundboard *soundboard)
{
    soundboard->KeyUp(mKey, mBeat);
}