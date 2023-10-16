/**
 * @file Item.h
 * @author Nam Hai Nguyen
 *
 * A base class for any items in the game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_ITEM_H
#define ACTIONSUDOKU_SUDOKULIB_ITEM_H

#include<string>
#include<memory>

#include "Declaration.h"

class Game;
/**
 * A base class for any items in the game
 */
class Item
{
private:
    /// The game that this item belongs to
    Game   *mGame;

    ///Location in the mainframe
    int mX, mY ;

    ///Row and column in the game
    double mRow, mCol;

    /// The image for this Item
    std::unique_ptr<wxImage> mImage;

    /// The item bitmap
    wxGraphicsBitmap mBitmap;

    ///Corresponding declaration of this item
    std::shared_ptr<Declaration> mDeclaration;

public:
    Item(Game *game);
    Item() = delete;
    Item(const Item &) = delete;
    virtual ~Item();

    /**
     * Get the id of item
     * @return id of item
     */
    std::wstring GetId() { return mDeclaration->GetId(); };
    /**
     * Get the X location of the item
     * @return X location of the item in the game
     */
    int GetX() { return mX;};
    /**
     * Get the Y location of the item
     * @return Y location of the item in the game
     */
    int GetY() { return mY; };
    /**
     * Set the location of the item
     * @param x : x coordinate
     * @param y : y coordinate
     */
    void SetLocation(int x, int y) { mX = x; mY = y;};
    /**
     * Get the declaration of an item
     * @return declaration of the item
     */
    std::shared_ptr<Declaration> GetDeclaration() { return mDeclaration; };
    /**
     * Set the declaration for an item
     * @param declaration : declaration we want to set
     */
    virtual void SetDeclaration(std::shared_ptr<Declaration> declaration) { mDeclaration = declaration; };
    std::wstring GetImagesDirectory();

    virtual bool HitTest(int x, int y);
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    virtual void XmlLoad(wxXmlNode *node);
};

#endif //ACTIONSUDOKU_SUDOKULIB_ITEM_H
