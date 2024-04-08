/**
 * @file ItemLoadVisitor.cpp
 * @author Alex Beck
 */

#include "pch.h"
#include "ItemLoadVisitor.h"
#include "Item.h"
#include "Meter.h"
#include "Scoreboard.h"
#include "Soundboard.h"
#include "Image.h"

void ItemLoadVisitor::VisitItem(Item *item)
{
    if (item->GetID() == mID)
    {
        item->XmlItemLoad(mNode);
    }
}

void ItemLoadVisitor::VisitMeter(Meter *meter)
{
    VisitItem(meter);
}

void ItemLoadVisitor::VisitScoreboard(Scoreboard *scoreboard)
{
    VisitItem(scoreboard);
}

void ItemLoadVisitor::VisitSoundboard(Soundboard *soundboard)
{
    VisitItem(soundboard);
}

void ItemLoadVisitor::VisitImage(Image *image)
{
    VisitItem(image);
}