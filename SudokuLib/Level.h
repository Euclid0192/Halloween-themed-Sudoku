/**
 * @file Level.h
 * @author Lewi Anamo
 *
 *
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_LEVEL_H
#define ACTIONSUDOKU_SUDOKULIB_LEVEL_H


#include "SudokuGame.h"

/**
 * Class that will read a levels XML file and construct the necessary objects
 */
class Level
{
private:
    /// Pointer to our game class
    Game* mGame;

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
    //Level() = delete;

    ///Copy constructor (disabled)
    //Level(const Level &) = delete;

    void Load(const wxString &filename);
    void XmlDeclaration(wxXmlNode *node);
    void XmlItem(wxXmlNode *node);

    void SetGame(Game* game) { mGame = game; }

    //when level change menu is pressed read the correct XML file
    // Should main load occur in the SudokuGame class since it know about all other classes
    //Need to calculate screen pixel size and pass to MainFrame
};

#endif //ACTIONSUDOKU_SUDOKULIB_LEVEL_H
