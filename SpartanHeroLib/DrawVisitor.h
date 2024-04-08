/**
 * @file DrawVisitor.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_DRAWVISITOR_H
#define SPARTANHERO_SPARTANHEROLIB_DRAWVISITOR_H

#include <memory>

#include "DeclarationVisitor.h"

/**
 * DrawVisitor draws all items in the level by calling
 * the Draw function of any Item objects
 */
class DrawVisitor : public DeclarationVisitor
{
private:

    /// The time from the last frame to the current frame
    double mTime;
    /// The current beat
    double mBeat;

    /// The graphics context to draw the item on
    wxGraphicsContext* mGraphics;

public:
    void operator=(const DrawVisitor &) = delete;
    DrawVisitor(const DrawVisitor &) = delete;
    DrawVisitor() = delete;

    /**
     * Constructor
     * @param time The current time of the song (in beats)
     * @param graphics The graphics context to draw on
     * @param beat the current beat
     */
    DrawVisitor(double time, double beat, wxGraphicsContext* graphics) : mTime(time), mBeat(beat), mGraphics(graphics) {}

    void VisitSoundboard(Soundboard* soundboard) override;

    void VisitScoreboard(Scoreboard* scoreboard) override;

    void VisitMeter(Meter* meter) override;

    void VisitItem(Item *item) override;

    void VisitImage(Image *image) override;
};

#endif //SPARTANHERO_SPARTANHEROLIB_DRAWVISITOR_H
