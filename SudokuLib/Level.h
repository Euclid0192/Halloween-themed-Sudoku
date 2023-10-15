/**
 * @file Level.h
 * @author Lewi Anamo
 *
 *
 */

#ifndef TARTARUS_SUDOKULIB_LEVEL_H
#define TARTARUS_SUDOKULIB_LEVEL_H

#include "SudokuGame.h"

/**
 * Class that will read a levels XML file and construct the necessary objects
 */
class Level
{
private:
    /// Width of a tile in pixels
    int tileWidth = 0;

    /// Height of a tile in pixels
    int tileHeight = 0;

    /// Width of screen in tiles
    int screenWidth = 0;

    /// Height of screen in tiles
    int screenHeight = 0;

public:
    /// Default constructor (disabled)
    Level() = delete;

    ///Copy constructor (disabled)
    Level(const Level &) = delete;

    //when game starts load up level 0

    //when level change menu is pressed read the correct XML file
    // Should main load occur in the SudokuGame class since it know about all other classes
    //Need to calculate screen pixel size and pass to MainFrame
};

#endif //TARTARUS_SUDOKULIB_LEVEL_H
