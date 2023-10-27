/**
 * @file DigitVisitor.h
 * @author Lewi Anamo
 *
 *
 */

#ifndef TARTARUS_SUDOKULIB_DIGITVISITOR_H
#define TARTARUS_SUDOKULIB_DIGITVISITOR_H

#include "ItemVisitor.h"
#include "Digit.h"
#include "Container.h"

class DigitVisitor : public ItemVisitor
{
private:
    /// Value we want the digit to be
    int mWantedVal = 0;
    /// Row of the top-left sudoku grid and make sure the digit we find is out side of the sudoku board
    int mCheckingRow = 0;
    /// Col of the top-left sudoku grid and make sure the digit we find is out side of the sudoku board
    int mCheckingCol = 0;

    /// Pointer to a digit - if correct digit is found it will not be a nullptr
    Digit* mDigit = nullptr;
public:
    /**
     * Gives us the digit we just found
     * @return digit
     */
    Digit* GetDigit() { return mDigit; }
    /**
     * Set the values we will compare with the digit values
     * @param val
     */
    void SetCMPVals(int val, int row, int col) { mWantedVal = val; mCheckingRow = row; mCheckingCol = col; }

    /**
     * Checks if the digit we have right now is outside of the sudoku grid
     * @param digit
     */
    void VisitDigit(Digit *digit) override {
        ///Checks if the digit we have right now is outside of the sudoku grid
        if ( (digit->GetRow() < mCheckingRow || digit->GetRow() > (mCheckingRow+8)) || (digit->GetCol() < mCheckingCol || digit->GetCol() > (mCheckingCol+8)))
        {
            if (digit->GetValue() == mWantedVal){
                mDigit = digit;
            }
        }
    }

    /**
     * Override function to visit container
     * @param container : container to visit
     */
    void VisitContainer(Container *container) override
    {
        auto digits = container->GetDigits();
        for (auto digit: digits)
        {
            digit->Accept(this);
        }
    }

};

#endif //TARTARUS_SUDOKULIB_DIGITVISITOR_H
