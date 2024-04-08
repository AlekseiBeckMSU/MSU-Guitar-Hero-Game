/**
 * @file UpdateVisitor.cpp
 * @author Alex Beck
 */

#include "pch.h"

#include "UpdateVisitor.h"
#include "Item.h"
#include "Meter.h"
#include "Scoreboard.h"
#include "Soundboard.h"
#include "Image.h"

/**
 * the item visitor to visit
 * @param item the item we want to visit
 */
void UpdateVisitor::VisitItem(Item *item)
{
    item->Update(mDeltaTime);
}

/**
 * the meter visitor to visit
 * @param meter the meter we want to visit
 */
void UpdateVisitor::VisitMeter(Meter *meter)
{
    VisitItem(meter);
}

/**
 * the scoreboard visitor to visit
 * @param scoreboard the scoreboard we want to visit
 */
void UpdateVisitor::VisitScoreboard(Scoreboard *scoreboard)
{
    VisitItem(scoreboard);
}

/**
 * the soundboard visitor to visit
 * @param soundboard the soundboard we want to visit
 */
void UpdateVisitor::VisitSoundboard(Soundboard *soundboard)
{
    VisitItem(soundboard);
}

/**
 * the iamge visitor to visit
 * @param image the image we want to visit
 */
void UpdateVisitor::VisitImage(Image *image)
{
    VisitItem(image);
}
