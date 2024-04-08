/**
 * @file KeyDownVisitor.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "KeyDownVisitor.h"
#include "Soundboard.h"

void KeyDownVisitor::VisitSoundboard(Soundboard *soundboard)
{
    soundboard->KeyDown(mKey, mBeat);
}