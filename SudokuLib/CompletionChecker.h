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
    /// The game that owns this completion checker
    SudokuGame* mGame;
    /// The solution of the game
    Solver* mSolution;
    /// Determine whether the game is completed or not
    bool mComplete;

public:
    void SetGame(SudokuGame* game);

    void Solve();
    void CheckCompletion();
};

#endif //TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H
