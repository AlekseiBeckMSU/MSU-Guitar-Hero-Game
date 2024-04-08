/**
 * @file DeclarationVisitor.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_DECLARATIONVISITOR_H
#define SPARTANHERO_SPARTANHEROLIB_DECLARATIONVISITOR_H

class Soundboard;
class Scoreboard;
class Meter;
class Note;
class Item;
class Image;

/**
 * DeclarationVisitor is an abstract base class for other
 * visitors.  These visitors are accepted by all subclasses of
 * Declaration.
 */
class DeclarationVisitor
{
protected:

    /**
     * Constructor
     * Ensures this is an abstract class
     */
    DeclarationVisitor() {}

public:

    virtual ~DeclarationVisitor() {}

    /**
     * Visit a soundboard
     * @param soundboard the soundboard to visit
     */
    virtual void VisitSoundboard(Soundboard* soundboard) {}

    /**
     * Visit a scoreboard
     * @param scoreboard the scoreboarad to visit
     */
    virtual void VisitScoreboard(Scoreboard* scoreboard) {}

    /**
     * Visit a meter
     * @param meter the meter to visit
     */
    virtual void VisitMeter(Meter* meter) {}

    /**
     * Visit a note
     * @param note the note to visit
     */
    virtual void VisitNote(Note* note) {}

    /**
     * Visit an item
     * @param item The item to visit
     */
    virtual void VisitItem(Item *item) {}

    /**
     * Visit an image
     * @param image The image to visit
     */
    virtual void VisitImage(Image *image) {}

};

#endif //SPARTANHERO_SPARTANHEROLIB_DECLARATIONVISITOR_H
