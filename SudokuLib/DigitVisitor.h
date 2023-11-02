/**
 * @file DigitVisitor.h
 * @author Lewi Anamo
 *
 * Visitor for the Digit class
 */

#ifndef TARTARUS_SUDOKULIB_DIGITVISITOR_H
#define TARTARUS_SUDOKULIB_DIGITVISITOR_H

#include "ItemVisitor.h"
#include "Digit.h"
#include "Xray.h"

/**
 * Visitor for the Digit class
 */
class DigitVisitor : public ItemVisitor
{
private:
    /// Value we want the digit to be
    int mWantedVal = 0;
    /// Row of the top-left sudoku grid and make sure the digit we find is out side of the sudoku board
    int mCheckingRow = 0;
    /// Col of the top-left sudoku grid and make sure the digit we find is out side of the sudoku board
    int mCheckingCol = 0;
    /// Pointer to the Xray that we get using a visitor
    Xray *mXray = nullptr;
    /// Height of a tile
    int mTileHeight = 0;

    /// Pointer to a digit - if correct digit is found it will not be a nullptr
    Digit* mDigit = nullptr;
public:
    /**
     * Gives us the digit we just found
     * @return digit
     */
    Digit* GetDigit() { return mDigit; }

    /**
     * Set the values we will campare with the digit values
     * @param val
     */
    void SetCMPVals(int val, Xray *xray, int row, int col, int tilehieght)
    {
        mWantedVal = val;
        mXray = xray;
        mCheckingRow = row;
        mCheckingCol = col;
        mTileHeight = tilehieght;
    }

    /**
     * Checks if the digit we have right now is outside of the sudoku grid
     * @param digit
     */
    void VisitDigit(Digit *digit) override {
        ///Checks if the digit we have right now is outside of the sudoku grid
        if (digit->GetRow() < mCheckingRow || digit->GetRow() > (mCheckingRow+8) || digit->GetCol() < mCheckingCol || digit->GetCol() > (mCheckingCol+8))
        {
            if (!digit->GetEaten() && digit->GetValue() == mWantedVal){
                mDigit = digit;
            }
        }
    }

};

#endif //TARTARUS_SUDOKULIB_DIGITVISITOR_H
