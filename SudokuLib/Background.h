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

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
    * Accept a visitor
    */
    void Accept(ItemVisitor *visitor) override { visitor->VisitBackground(this); };
};

#endif //TARTARUS_SUDOKULIB_BACKGROUND_H
