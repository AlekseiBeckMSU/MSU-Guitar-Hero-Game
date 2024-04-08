/**
 * @file Declaration.h
 * @author Alex Beck
 *
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_DECLARATION_H
#define SPARTANHERO_SPARTANHEROLIB_DECLARATION_H

#include <memory>
#include "DeclarationVisitor.h"

class Level;

/**
 * Declaration represents an element in the XML
 * under the declarations tag
 */
class Declaration
{
private:

    double mWidth = 0; ///< The width of the item in virtual pixels
    double mHeight = 0; ///< The height of the item in virtual pixels

    /// The ID of this declaration
    std::wstring mID;

    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;

protected:
    Level * mLevel; ///< Level it belongs to

    Declaration(Level* level);

public:

    void operator=(const Declaration &) = delete;
    Declaration(const Declaration &) = delete;
    Declaration() = delete;
    ~Declaration();

    virtual void XmlDeclarationLoad(wxXmlNode *node);

    /**
     * Get the ID of this declaration
     * @return The ID of this declaration
     */
    std::wstring GetID() { return mID; }

    virtual void Draw(wxGraphicsContext* graphics, double x, double y);

    /**
     * Accept a declaration visitor
     * @param visitor The visitor to accept
     */
    virtual void Accept(DeclarationVisitor* visitor) = 0;


    /**
     * Getter to get width of declaration
     * @return Width value
     */
    double GetWidth(){return mWidth;}

    /**
     * Getter to get height of declaration
     * @return height value
     */
    double GetHeight(){return mHeight;}

};

#endif //SPARTANHERO_SPARTANHEROLIB_DECLARATION_H
