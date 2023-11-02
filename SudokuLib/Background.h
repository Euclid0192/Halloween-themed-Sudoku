/**
 * @file Background.h
 * @author Lewi Anamo
 *
 *
 */

#ifndef TARTARUS_SUDOKULIB_BACKGROUND_H
#define TARTARUS_SUDOKULIB_BACKGROUND_H

#include "Item.h"

#include <memory>

/**
 * A class for the Background item
 */
class Background : public Item
{
private:

public:
    Background(SudokuGame *game);
    Background() = delete;
    Background(const Background &) = delete;

    /**
     * Get the background height
     * @return height of background
     */
    int GetBackgroundHeight() { return GetHeight(); }
    /**
     * Get the background width
     * @return width of background
     */
    int GetBackgroundWidth() { return GetWidth(); }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
    * Accept a visitor
     * @param visitor: a visitor to be accepted
    */
    void Accept(ItemVisitor *visitor) override { visitor->VisitBackground(this); };
};

#endif //TARTARUS_SUDOKULIB_BACKGROUND_H
