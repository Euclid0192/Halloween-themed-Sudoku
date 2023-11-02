/**
 * @file CompletionChecker.h
 * @author Lewi Anamo
 *
 * Checks that the game is completed
 */

#ifndef TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H
#define TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H

#include "Solver.h"

class SudokuGame;

/**
 * Checks that the game is completed
 */
class CompletionChecker
{
private:
    SudokuGame* mGame;

    Solver* mSolution;

    bool mComplete;

public:
    void SetGame(SudokuGame* game);

    void Solve();
    void CheckCompletion();
};

#endif //TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H
