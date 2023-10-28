/**
 * @file CompletionChecker.cpp
 * @author anamo
 */

#include "pch.h"
#include "CompletionChecker.h"
#include "DigitVisitor.h"
#include "GetGridItemVisitor.h"
#include "SudokuGame.h"
#include "GetXrayVisitor.h"


void CompletionChecker::SetGame(SudokuGame* game)
{
    mGame = game;
    mSolution = mGame->GetSolution();
}

/**
 * Implements the solve functionality
 * Checks if a Sudoku board square is empty or not and prefoms and action as needed
 */
void CompletionChecker::Solve()
{
    int startRow = mSolution->GetRow();
    int startCol = mSolution->GetCol();
    int endRow = startRow + 8;
    int endCol = startCol + 8;
    int ind1 = 0; int ind2 = 0;

    GetXrayVisitor xrayVisit;
    mGame->Accept(&xrayVisit);
    auto xRay = xrayVisit.GetXray();

    // Will loop through the sudoku row and col checking if a grid is empty or not
    // if empty will move to next square if not it will find the right value to put in the square and
    // the digit
    for (int i = startRow; i <= endRow; i++){
        for (int j = startCol; j <= endCol; j++)
        {
            GetGridItemVisitor gridVisitor;
            gridVisitor.SetLocation(j, i);
            mGame->Accept(&gridVisitor);

            if (gridVisitor.GetResult()){
                ind2++;
                continue;
            }

            int wantedValue = mSolution->GetVectorValue(ind1, ind2);

            ///This visitor will give us the digit we want
            DigitVisitor visitor;
            visitor.SetCMPVals(wantedValue, xRay, startRow, startCol, mGame->GetTileHeight());
            mGame->Accept(&visitor);

            /// Implement the move functionality
            auto digit = visitor.GetDigit();
            double x = j * mGame->GetTileHeight();
            double y =  (i) * mGame->GetTileHeight();

            if (digit != nullptr)
            {
                digit->SetLocation(x,y);
                digit->SetColRow(i, j);
            }

            /// Also finding a way to think about the xRay, if a digit is eaten then don't move that as well

            ind2++;
        }
        ind1++;
        ind2 = 0;
    }

    CheckCompletion();
}

/**
 * Checks if the game is complete and what the solution is
 */
void CompletionChecker::CheckCompletion()
{
    int startRow = mSolution->GetRow();
    int startCol = mSolution->GetCol();
    int endRow = startRow + 8;
    int endCol = startCol + 8;
    int ind1 = 0; int ind2 = 0;
    bool anyIncorrect = false;

    for (int i = startRow; i <= endRow; i++){
        for (int j = startCol; j <= endCol; j++)
        {
            GetGridItemVisitor gridVisitor;
            gridVisitor.SetLocation(j, i);
            mGame->Accept(&gridVisitor);

            if (!gridVisitor.GetResult()){
                /// If a grid is empty end the loop, game is not complete
                return;
            }

            int wantedValue = mSolution->GetVectorValue(ind1, ind2);

            if (gridVisitor.GetDigit()->GetValue() != wantedValue)
            {
                ///Indicate that at some point a wrong value was put into the wrong place
                /// Set some bool value
                anyIncorrect = true;
            }

            ind2++;
        }
        ind1++;
        ind2 = 0;
    }

    ///Check bool value and display window
    /// update the bools for correct and incorrect and make a draw function similar to intro page
    if (anyIncorrect){
        mGame->SetIncorrect(true);
    } else {
        mGame->SetCorrect(true);
    }
}
