/**
 * @file Image.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_IMAGE_H
#define SPARTANHERO_SPARTANHEROLIB_IMAGE_H

#include "Item.h"
#include "Declaration.h"
#include "DeclarationVisitor.h"

/**
 * Image represents a static image in the level
 */
class Image : public Item
{
private:

public:
    explicit Image(Level *level);

	/**
	 * the function to accept the visitor into the image
	 * @param visitor the visitor to accpet
	 */
    void Accept(DeclarationVisitor *visitor) override {visitor->VisitImage(this);}
};

#endif //SPARTANHERO_SPARTANHEROLIB_IMAGE_H
