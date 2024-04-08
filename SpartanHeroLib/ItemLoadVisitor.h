/**
 * @file ItemLoadVisitor.h
 * @author Alex Beck
 *
 * ItemLoadVisitor is a declaration visitor which handles
 * loading extra XML data for Item objects from inside the items
 * tag.
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_ITEMLOADVISITOR_H
#define SPARTANHERO_SPARTANHEROLIB_ITEMLOADVISITOR_H

#include "DeclarationVisitor.h"

/**
 * ItemLoadVisitor is a declaration visitor which handles
 * loading extra XML data for Item objects from inside the items
 * tag.
 */
class ItemLoadVisitor : public DeclarationVisitor
{
private:
    /// The item id to load
    std::wstring mID;

    /// The node to load the item from
    wxXmlNode * mNode;
public:

    /**
     * Constructor
     * @param id
     * @param node
     */
    ItemLoadVisitor(std::wstring id, wxXmlNode *node) : mID(id), mNode(node) {}

    /**
     * Visit a soundboard
     * @param soundboard
     */
    void VisitSoundboard(Soundboard* soundboard) override;

    /**
     * Visit a scoreboard
     * @param scoreboard
     */
    void VisitScoreboard(Scoreboard* scoreboard) override;

    /**
     * Visit a meter
     * @param meter
     */
    void VisitMeter(Meter* meter) override;

    /**
     * Visit an item
     * @param item The item to visit
     */
    void VisitItem(Item *item) override;

    /**
     * Visit an Image
     * @param image
     */
    void VisitImage(Image *image) override;
};

#endif //SPARTANHERO_SPARTANHEROLIB_ITEMLOADVISITOR_H
