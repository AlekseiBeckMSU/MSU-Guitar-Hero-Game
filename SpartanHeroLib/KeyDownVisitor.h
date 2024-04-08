/**
 * @file KeyDownVisitor.h
 * @author Alex Beck
 *
 *
 * process a key press event for a Soundboard object
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_KEYDOWNVISITOR_H
#define SPARTANHERO_SPARTANHEROLIB_KEYDOWNVISITOR_H

#include "DeclarationVisitor.h"

/**
 * process a key press event for a Soundboard object
 *
 */
class KeyDownVisitor : public DeclarationVisitor
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
    KeyDownVisitor(wchar_t key, double beat) : mKey(key), mBeat(beat) {}

    /**
     *
     * @param soundboard
     */
    virtual void VisitSoundboard(Soundboard* soundboard);
};

#endif //SPARTANHERO_SPARTANHEROLIB_KEYDOWNVISITOR_H
