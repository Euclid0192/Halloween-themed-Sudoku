/**
 * @file Item.h
 * @author Nam Hai Nguyen
 *
 * A base class for any items in the game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_ITEM_H
#define ACTIONSUDOKU_SUDOKULIB_ITEM_H

#include "ItemVisitor.h"
#include<string>
#include<memory>
#include <wx/xml/xml.h>


class SudokuGame;
/**
 * A base class for any items in the game
 */
class Item
{
private:
    /// The game that this item belongs to
    SudokuGame   *mGame;

    ///id of Declaration
    std::wstring mId;

    ///Width and Height
    int mWidth, mHeight;

    ///Location in the mainframe
    wxPoint2DDouble mLocation;

    ///Row and column in the game
    double mRow, mCol;

    /// The image for this Item
    std::shared_ptr<wxImage> mImage;

    /// The item bitmap
    wxGraphicsBitmap mBitmap;

public:
    Item(SudokuGame *game);
    Item() = delete;
    Item(const Item &);
    virtual ~Item();

    /**
     * Get the id of item
     * @return id of item
     */
    std::wstring GetId() { return mId; };
    /**
     * Get the width of the item
     * @return width of item
     */
    int GetWidth() { return mWidth; };
    /**
     * Get the height of the item
     * @return height of item
     */
    int GetHeight() { return mHeight;};
    /**
     * Get the X location of the item
     * @return X location of the item in the game
     */

    /**
     * Getter for row
     * @return row of item
     */
    double GetRow() { return mRow; };
    /**
     * Getter for column
     * @return column of item
     */
    double GetCol() { return mCol; };
    double GetX() { return mLocation.m_x;};
    /**
     * Get the Y location of the item
     * @return Y location of the item in the game
     */
    double GetY() { return mLocation.m_y; };
    /**
     * Get the location of the item
     * @return location of item in wxPoint2DDouble
     */
    wxPoint2DDouble GetLocation() { return mLocation; };
    /**
     * Set the location of the item
     * @param x : x coordinate
     * @param y : y coordinate
     */
    void SetLocation(double x, double y) { mLocation.m_x = x; mLocation.m_y = y;};
    /**
    * Set the row and col location of the item
    * @param x : x coordinate
    * @param y : y coordinate
    */
    void SetColRow(double row, double col) { mRow = row; mCol = col; }
    std::wstring GetImagesDirectory();

    /**
     * Test if this item is at location x, y
     * @param x: X location
     * @param y: Y location
     * @return: true if this item is at (x, y); false otherwise
     */
    virtual bool HitTest(double x, double y) { return false; };
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    virtual void Update(double elapsed) {};

    virtual void SaveDeclaration(wxXmlNode *node) {};
    virtual void SaveItem(wxXmlNode *node) {};
    virtual void XmlLoadDeclaration(wxXmlNode *node);
    virtual void XmlLoadItem(wxXmlNode *node);

    virtual std::shared_ptr<Item> Clone() { return nullptr; };
    /**
     * Accept a visitor
     * @param visitor
     */
    virtual void Accept(ItemVisitor *visitor) = 0;

    /**
     * Get the bitmap of the item
     * @return bitmap of the item
     */
    wxGraphicsBitmap GetBitmap() { return mBitmap; }
    /**
     * Get the image of the item
     * @return image of the item
     */
    std::shared_ptr<wxImage> GetImage() { return mImage; }
    /**
     * Getter for the game this item belongs to
     * @return pointer to the game
     */
    SudokuGame *GetGame() { return mGame; };
};

#endif //ACTIONSUDOKU_SUDOKULIB_ITEM_H
