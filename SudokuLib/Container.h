/**
 * @file Container.h
 * @author yaxuan
 *
 * The class for containers
 */

#ifndef TARTARUS_SUDOKULIB_CONTAINER_H
#define TARTARUS_SUDOKULIB_CONTAINER_H

#include <random>
#include "Item.h"

/**
 * The class for containers
 */
class Container : public Item
{
private:
    ///Front image of Container
    std::unique_ptr<wxImage> mFrontImage;
    ///Bitmap of front image
    wxGraphicsBitmap mFrontBitmap;
    ///Digits in the container
    std::vector<std::shared_ptr<Item>> mDigits;
	/// Random number generator
	std::mt19937 mRandom;


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
	bool HitTest(double x, double y) override;

	/**
	 * Get the random number generator
	 * @return Pointer to the random number generator
	 */
	std::mt19937 &GetRandom() {return mRandom;}

	/**
	 * Empties the Container of its Digits
	 */
	void Empty();

	/**
	 * Clears the vector of Digits
	 */
	void Clear();

    /**
     * Get all the digits in the container
     * @return vector of digits
     */
    std::vector<std::shared_ptr<Item>> GetDigits() { return mDigits; }

    /**
    * Accept a visitor
    */
    void Accept(ItemVisitor *visitor) override { visitor->VisitContainer(this); }
};

#endif //TARTARUS_SUDOKULIB_CONTAINER_H
