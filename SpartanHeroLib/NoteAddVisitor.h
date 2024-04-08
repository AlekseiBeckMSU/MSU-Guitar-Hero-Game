/**
 * @file NoteAddVisitor.h
 * @author Alex Beck
 *
 * Header file for the NoteAddVisitor class
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_NOTEADDVISITOR_H
#define SPARTANHERO_SPARTANHEROLIB_NOTEADDVISITOR_H

#include <memory>
#include "DeclarationVisitor.h"
#include "NoteTiming.h"

/**
 * A visitor which adds a note timing to
 * the soundboard class
 */
class NoteAddVisitor : public DeclarationVisitor
{
private:
    /// pointer to notetiming class
    std::shared_ptr<NoteTiming> mTiming;
public:
    NoteAddVisitor(std::shared_ptr<NoteTiming> timing);

    void VisitSoundboard(Soundboard *soundboard) override;
};

#endif //SPARTANHERO_SPARTANHEROLIB_NOTEADDVISITOR_H
