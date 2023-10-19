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

#include "Item.h"
#include "Game.h"

#include <memory>

/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

/// Top left corner of the scoreboard in virtual pixels
const wxPoint ScoreboardTopLeft(10, 10);

/**
 * Class for Scoreboard
 */
class ScoreBoard : public wxWindow
{
private:
    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    int mTime = 0;

public:
    ///
    ScoreBoard();

    void UpdateTime(wxTimerEvent &event);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double scale,
              double XOffset, double YOffset);


};

#endif //TARTARUS_SUDOKULIB_SCOREBOARD_H