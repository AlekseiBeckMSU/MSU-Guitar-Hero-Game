/**
 * @file Item.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_ITEM_H
#define SPARTANHERO_SPARTANHEROLIB_ITEM_H

#include <memory>
#include "Declaration.h"

class Level;
class Scoreboard;
/**
 * An Item to be displayed in the GameView
 */
class Item : public Declaration
{
private:
    double mX = 0; ///< The position of the center of the object in the x direction (in virtual pixels)
    double mY = 0; ///< The position of the center of the object in the y direction (in virtual pixels)

protected:

    /**
     * COnstructor
     * @param level
     */
    Item(Level *level) : Declaration(level) {}

public:

    virtual void XmlItemLoad(wxXmlNode *node);

	/**
	 * update funciton for item
	 * @param time the time we use
	 */
    virtual void Update(double time) {}
    virtual void Draw(wxGraphicsContext *graphics, double beat);

    /**
     * Set the location of this item
     * @param x The x location of the center of the item (virtual pixels)
     * @param y The y location of the center of the item (virtual pixels)
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    virtual void Accept(DeclarationVisitor* visitor);

    /**
     * getter for x
     * @return the x pos
     */
    double GetX(){return mX;}
	/**
	 * getter for y
	 * @return the y pos
	 */
    double GetY(){return mY;}
};

#endif //SPARTANHERO_SPARTANHEROLIB_ITEM_H
