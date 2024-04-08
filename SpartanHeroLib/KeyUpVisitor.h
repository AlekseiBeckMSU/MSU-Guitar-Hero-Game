/**
 * @file KeyUpVisitor.h
 * @author Alex Beck
 *
 * process a key press event for a Soundboard object
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_KEYUPVISITOR_H
#define SPARTANHERO_SPARTANHEROLIB_KEYUPVISITOR_H

#include "DeclarationVisitor.h"

/**
 * process a key press event for a Soundboard object
 *
 */
class KeyUpVisitor : public DeclarationVisitor
{
private:
    wchar_t mKey; ///< Key value
    double mBeat; ///< Beat value
public:
    /**
     *
     * @param key
     * @param beat
     */
    KeyUpVisitor(wchar_t key, double beat) : mKey(key), mBeat(beat) {}

    /**
     *
     * @param soundboard
     */
    void VisitSoundboard(Soundboard* soundboard) override;
};

#endif //SPARTANHERO_SPARTANHEROLIB_KEYUPVISITOR_H
