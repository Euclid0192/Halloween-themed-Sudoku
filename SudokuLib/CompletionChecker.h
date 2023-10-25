/**
 * @file CompletionChecker.h
 * @author Lewi Anamo
 *
 *
 */

#ifndef TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H
#define TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H

#include "SudokuGame.h"
#include "Solver.h"

class CompletionChecker
{
private:
    SudokuGame* mGame;

    Solver* mSolution;

public:
    void SetGame(SudokuGame* game);

    void Solve();
    void CheckCompletion();
};

#endif //TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H
