/**
 * @file GetGridItemVisitor.h
 * @author Lewi Anamo
 *
 *  Visitor to find if any item is one a square on the Sudoku Grid
 */

#ifndef TARTARUS_SUDOKULIB_GETGRIDITEMVISITOR_H
#define TARTARUS_SUDOKULIB_GETGRIDITEMVISITOR_H

#include "ItemVisitor.h"
#include "Digit.h"
#include "Container.h"

/**
 *  Visitor to find if any item is one a square on the Sudoku Grid
 */
class GetGridItemVisitor : public ItemVisitor
{
private:
    /// The row we want to the digit to be at
    int  mWantedRow = 0;
    /// The col we want to the digit to be at
    int  mWantedCol = 0;

    /// Tells us whether the Sudoku square is empty or not
    bool mGridTake = false;
    Digit* mDigit = nullptr;
	Container* mContainer = nullptr;

public:
    /**
     * Tells us whether we found a digit that is at the location
     * @return bool
     */
    bool GetResult() { return mGridTake; }
    Digit* GetDigit() { return mDigit; }

    /**
     * Set the location in the sudoku grid that we will compare with
     * @param col
     * @param row
     */
    void SetLocation(int col, int row) { mWantedCol = col; mWantedRow = row; }

    void VisitDigit(Digit *digit) override
	{
        if (digit->GetCol() == mWantedCol && digit->GetRow() == mWantedRow)
        {
            mGridTake = true;
            mDigit = digit;
        }
    }

};

#endif //TARTARUS_SUDOKULIB_GETGRIDITEMVISITOR_H
