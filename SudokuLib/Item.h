/**
 * @file Item.h
 * @author Nam Hai Nguyen
 *
 * A base class for any items in the game
 */

#ifndef TARTARUS_SUDOKULIB_ITEM_H
#define TARTARUS_SUDOKULIB_ITEM_H

#include<string>
#include<memory>

class Game;
/**
 * A base class for any items in the game
 */
class Item
{
private:
    /// The game that this item belongs to
    Game   *mGame;

    ///id of item
    std::wstring mId;
    ///Location in the mainframe
    int mX, mY ;

    ///Width and Height
    int mWidth, mHeight;

    ///Row and column in the game
    int mRow, mCol;

    /// The image for this item
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap for this item
    std::unique_ptr<wxBitmap> mItemBitmap;

public:
    Item(Game *game);
    Item() = delete;
    Item(const Item &) = delete;
    virtual ~Item();
    virtual void SetImage(const std::wstring &path);

    /**
     * Get id of item
     * @return id of item
     */
    std::wstring GetId() { return mId; };
    /**
     * Get the X location of the item
     */
    int GetX() { return mX;};
    /**
     * Get the Y location of the item
     */
    int GetY() { return mY; };
    /**
     * Set the location of the item
     * @param x : x coordinate
     * @param y : y coordinate
     */
    void SetLocation(int x, int y) { mX = x; mY = y;};

    /**
     * Get the mRow of the item
     */
    int GetRow() { return mRow;};
    /**
     * Setter for mRow
     * @param row : value to be set
     */
    void SetRow(int row) { mRow = row; };
    /**
     * Get the mCol of the item
     */
    int GetCol() { return mCol; };
    /**
     * Setter for mCol
     * @param col
     */
    void SetCol(int col) { mCol = col; };

    virtual bool HitTest(int x, int y);
    virtual void Draw(wxDC *dc);
    virtual void XmlLoadDeclaration(wxXmlNode *node);
    void XmlLoadItem(wxXmlNode *node);
};

#endif //TARTARUS_SUDOKULIB_ITEM_H
