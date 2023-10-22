/**
 * @file Game.h
 * @author Nam Hai Nguyen
 *
 * Class that implements a sudoku game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_GAME_H
#define ACTIONSUDOKU_SUDOKULIB_GAME_H

#include "Item.h"
#include "Sparty.h"
#include "ItemVisitor.h"
#include "Level.h"
#include "Solver.h"
#include "ScoreBoard.h"

#include<string>
#include<map>
#include<memory>
#include<vector>

class Game
{
private:
    ///All items in the Declarations
    std::map<std::wstring, std::shared_ptr<Item>> mDeclarations;
    ///All items that appear in the real game
    std::vector<std::shared_ptr<Item>> mItems;
    /// Directory containing the system images
    std::wstring mImagesDirectory;
    ///Directory containing the level xml files
    std::wstring mLevelsDirectory;

    ///Scale for virtual pixel
    double mScale = 0;
    /// X offset for virtual pixel
    double mXOffset = 0;
    /// Y offset for virtual pixel
    double mYOffset = 0;
    ///Sparty
    Sparty *mSparty;
    ///Tile width and height
    int mTileWidth;
    int mTileHeight;
    ///width and height of the game
    int mWidth;
    int mHeight;
    ///Solver class
    Solver mSolution;

    ///Scoreboard
    ScoreBoard mScoreBoard;

public:
    Game();
    /**
     * Destructor
     */
    virtual ~Game() = default;

    void AddDeclaration(std::shared_ptr<Item> declaration);
    void AddItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> HitTest(int x, int y);
    void MoveToFront(std::shared_ptr<Item> item);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void OnLeftDown(double x, double y);
    void OnKeyDown(wxKeyEvent &event);
    void Clear();

    void Update(double elapsed);

    /**
     * Get the directory the images are stored in
     * @return Images directory path
     */
    const std::wstring &GetImagesDirectory() const { return mImagesDirectory; }
    void SetImagesDirectory(const std::wstring &dir);
    void Accept(ItemVisitor *visitor);
    std::shared_ptr<Item> GetDeclaration(std::wstring id) { return mDeclarations[id]; }
    void SetSparty(Sparty *sparty) { mSparty = sparty; }

    /**
     * Get the tile Width
     */
    int GetTileWidth() { return mTileWidth; }
    /**
     * Get the tile height
     */
    int GetTileHeight() { return mTileHeight; }
    /**
     * Set the tile width and height
     * @param width
     * @param height
     */
    void SetTileDimension(int width, int height) { mTileWidth = width, mTileHeight = height;}
    /**
     * Get the width of the game
     * @return width of the game
     */
    int GetWidth() { return mWidth; }
    /**
     * Get the height of the game
     * @return height of the game
     */
    int GetHeight() { return mHeight; }
    /**
     * Set the width and height of the game
     * @param width
     * @param height
     */
    void SetGameDimension(int width, int height) { mWidth = width; mHeight = height; }

     /**
      * Getter functino of its scale
      */
      const double getScale() {return mScale;}

     /**
     * Getter functino of XOffset
     */
      double getXOffset() {return mXOffset;}

     /**
      * Getter functino of YOffset
      */
      double getYOffset() {return mYOffset;}

      void SaveDeclarations(wxXmlNode *node);
      void SaveItems(wxXmlNode *node);
      void SaveSolver(wxXmlNode *node);
      void DrawIntroPage();
};

#endif //ACTIONSUDOKU_SUDOKULIB_GAME_H
