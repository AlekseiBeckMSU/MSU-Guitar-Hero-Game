/**
 * @file UpdateVisitor.h
 * @author Alex Beck
 *
 * Visitor to update items in game
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_UPDATEVISITOR_H
#define SPARTANHERO_SPARTANHEROLIB_UPDATEVISITOR_H

#include "DeclarationVisitor.h"

/**
 * Visitor to update items in game
 */
class UpdateVisitor : public DeclarationVisitor
{
private:
    /// Delta time value
    double mDeltaTime;
public:
    /**
     * Constructor
     * @param deltaTime
     */
    UpdateVisitor(double deltaTime) : mDeltaTime(deltaTime) {}


    void VisitSoundboard(Soundboard* soundboard) override;
    void VisitScoreboard(Scoreboard* scoreboard) override;
    void VisitMeter(Meter* meter) override;
    void VisitItem(Item *item) override;
    void VisitImage(Image *image) override;
};

#endif //SPARTANHERO_SPARTANHEROLIB_UPDATEVISITOR_H
