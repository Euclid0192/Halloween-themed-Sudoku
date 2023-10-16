/**
 * @file ScoreBoard.h
 * @author Lewi Anamo
 *
 *
 */

#ifndef TARTARUS_SUDOKULIB_SCOREBOARD_H
#define TARTARUS_SUDOKULIB_SCOREBOARD_H

class ScoreBoard
{
private:
    int mMinutes;
    int mSeconds;
public:
    ///
    ScoreBoard();

    void UpdateTime();

    void Draw(wxDC* graphics);

};

#endif //TARTARUS_SUDOKULIB_SCOREBOARD_H
