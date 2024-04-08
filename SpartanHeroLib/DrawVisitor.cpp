/**
 * @file DrawVisitor.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "DrawVisitor.h"
#include "Item.h"
#include "Meter.h"
#include "Scoreboard.h"
#include "Soundboard.h"
#include "Image.h"

/**
 * visits item to draw
 * @param item the item we visit
 */
void DrawVisitor::VisitItem(Item *item)
{
    item->Update(mTime);
    item->Draw(mGraphics, mBeat);
}

/**
 * visits the meter to draw
 * @param meter the meter we visit
 */
void DrawVisitor::VisitMeter(Meter *meter)
{
    VisitItem(meter);
}

/**
 * vvisits the scoreboard to draw
 * @param scoreboard the scoreboard we visit
 */
void DrawVisitor::VisitScoreboard(Scoreboard *scoreboard)
{
    VisitItem(scoreboard);
}

/**
 * visits the soundboard to draw
 * @param soundboard the soundboard we visit
 */
void DrawVisitor::VisitSoundboard(Soundboard *soundboard)
{
    VisitItem(soundboard);
}

/**
 * visits the image to draw
 * @param image the image we visit
 */
void DrawVisitor::VisitImage(Image *image)
{
    VisitItem(image);
}