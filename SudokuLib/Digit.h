/**
 * @file Digit.h
 * @author Nam Hai Nguyen
 *
 * The digit in the sudoku game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_DIGIT_H
#define ACTIONSUDOKU_SUDOKULIB_DIGIT_H

#include "Item.h"

/**
 * The digit in the sudoku game
 */
class Digit : public Item
{
private:

public:
    Digit() = delete;
    Digit(const Digit &) = delete;
    Digit(Game *game);
};

#endif //ACTIONSUDOKU_SUDOKULIB_DIGIT_H
