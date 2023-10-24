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
    ///The value of the digit, 0-8
    int mValue;
    ///Determine if this is given or playing digit
    bool mGiven = false;
public:
    Digit() = delete;
    Digit(const Digit &);
    Digit(SudokuGame *game);

    void XmlLoadDeclaration(wxXmlNode *node) override;
    std::shared_ptr<Item> Clone() override;
    /**
     * Get the value of this digit
     * @return int value of digit
     */
    int GetValue() { return mValue; }
    /**
     * Gets the mGiven value whether this is a given or not
     *  @return bool
     */
     bool GetGiven() { return mGiven; }
    /**
    * Get the row location of the digit
    * @return row location of the digit in the game
    */
     int GetRow() { return Item::GetRow(); }
    /**
    * Get the col location of the digit
    * @return col location of the digit in the game
    */
     int GetCol() { return Item::GetCol(); }
    /**
     * Accept a visitor
     */
    void Accept(ItemVisitor *visitor) override { visitor->VisitDigit(this); };
    bool HitTest(double x, double y) override;
};

#endif //ACTIONSUDOKU_SUDOKULIB_DIGIT_H
