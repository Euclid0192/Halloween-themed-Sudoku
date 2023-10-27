/**
 * @file Container.h
 * @author yaxuan
 *
 * The class for containers
 */

#ifndef TARTARUS_SUDOKULIB_CONTAINER_H
#define TARTARUS_SUDOKULIB_CONTAINER_H

#include "Item.h"

class Container : public Item
{
private:
    ///Front image of Container
    std::unique_ptr<wxImage> mFrontImage;
    ///Bitmap of front image
    wxGraphicsBitmap mFrontBitmap;
    ///Digits in the container
    std::vector<std::shared_ptr<Item>> mDigits;
public:
    ///Default constructor (disabled)
    Container() = delete;

    /// Copy constructor (disabled)
    Container(const Container &) = delete;

    /// Assignment operator
    void operator=(const Container &) = delete;

    Container(SudokuGame *game);
    void XmlLoadDeclaration(wxXmlNode *node) override;
    void XmlLoadItem(wxXmlNode *node) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * Get all the digits in the container
     * @return vector of digits
     */
    std::vector<std::shared_ptr<Item>> GetDigits() { return mDigits; }

    /**
    * Accept a visitor
    */
    void Accept(ItemVisitor *visitor) override { visitor->VisitContainer(this); };
};

#endif //TARTARUS_SUDOKULIB_CONTAINER_H
