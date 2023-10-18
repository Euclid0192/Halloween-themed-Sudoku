/**
 * @file Sparty.h
 * @author Nam Hai Nguyen
 *
 * The moving Sparty, main character of the game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_SPARTY_H
#define ACTIONSUDOKU_SUDOKULIB_SPARTY_H

#include "Item.h"
#include "Declaration.h"
#include "SpartyDeclaration.h"

#include<string>
#include<memory>

/**
 * The main character of the game
 */
class Sparty : public Item
{
private:
    ///Images of Sparty
    std::unique_ptr<wxImage> mImage1, mImage2;
    ///Bitmaps of Sparty
    wxGraphicsBitmap mBitmap1, mBitmap2;

    double mSpeedX;
    ///Speed in Y direction
    double mSpeedY;
public:
    Sparty() = delete;
    Sparty(const Sparty &) = delete;
    Sparty(Game *game);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode *node) override;
};

#endif //ACTIONSUDOKU_SUDOKULIB_SPARTY_H
