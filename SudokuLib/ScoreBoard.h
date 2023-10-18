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
    ///set up for time
    int mTime;
    wxTimer mTimer;
public:
    ///
    ScoreBoard();

    void UpdateTime(wxTimerEvent &event);

    void Draw(std::shared_ptr<wxGraphicsContext> graph);

};

#endif //TARTARUS_SUDOKULIB_SCOREBOARD_H
