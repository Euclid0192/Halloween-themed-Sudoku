/**
 * @file ScoreBoard.h
 * @author Lewi Anamo
 * @author Yaxuan Tang
 *
 * Class for score board
 *
 */

#ifndef TARTARUS_SUDOKULIB_SCOREBOARD_H
#define TARTARUS_SUDOKULIB_SCOREBOARD_H


#include <memory>

/**
 * Class for Scoreboard
 */
class ScoreBoard
{
private:
    /// The last stopwatch time
    double mTime = 0;

public:
    /// Constructor
    ScoreBoard();

    void UpdateTime(double last);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void RefreshTime();

    /**
     * Getter for mTime
     * @return : the current time in decimal seconds
     */
     double GetTime(){
         return mTime;
     }

    void Stop();

    void Restart();

};

#endif //TARTARUS_SUDOKULIB_SCOREBOARD_H