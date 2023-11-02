/**
 * @file CompletionChecker.h
 * @author Lewi Anamo
 *
 *  Class that checks if the game is complete and if the answers are correct
 */

#ifndef TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H
#define TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H

#include "Solver.h"


class SudokuGame;

/**
*  Class that checks if the game is complete and if the answers are correct
*/
class CompletionChecker
{
private:
    ///Holds our game object which we will check
    SudokuGame* mGame;
    ///Hold the object which has our solutions
    Solver* mSolution;

public:
    void SetGame(SudokuGame* game);

    void Solve();
    void CheckCompletion();
};

#endif //TARTARUS_SUDOKULIB_COMPLETIONCHECKER_H
