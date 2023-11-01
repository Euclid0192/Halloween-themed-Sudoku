/**
 * @file SudokuGame.h
 * @author Nam Hai Nguyen, Olivia Pal
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
#include "CompletionChecker.h"

#include "Popup.h"

#include<string>
#include<map>
#include<memory>
#include<vector>
#include <random>


class SudokuGame
{
private:
    ///All items in the Declarations
    std::map<std::wstring, std::shared_ptr<Item>> mDeclarations;
    ///All items that appear in the real game
    std::vector<std::shared_ptr<Item>> mItems;
    /// Directory containing the system images
    std::wstring mImagesDirectory;


    ///All popups
    std::vector<Popup*> mPopups;

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
    ///Object that will check if our board has the correct answer
    CompletionChecker mChecker;
    /// Holds the level class that is passed from view class
    Level* mLevel;
    /// Tells the game if the game is complete and answer is incorrect
    bool mIncorrect = false;
    /// Tells the game if the game is complete and answer is correct
    bool mCorrect = false;

    ///Store the current level for instruction page
    int mCurrentLevel = 0;

    std::mt19937 mRandom;
    ///Determine when the digits should floating around
    bool mFloatingDigits = false;
public:
    SudokuGame();
    /**
     * Destructor
     */
    virtual ~SudokuGame() = default;

    void AddDeclaration(std::shared_ptr<Item> declaration);
    void AddItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> HitTest(double x, double y);
    void MoveToFront(std::shared_ptr<Item> item);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void OnLeftDown(double x, double y);
    void OnKeyDown(wxKeyEvent &event);
    void Clear();

    void Update(double elapsed);

    ///
    void AddPopup(std::wstring message);
    void RemovePopup(Popup *popup);
    ///

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
    * Get the solver class object
    * @return Solver class
    */
    Solver* GetSolution() { return &mSolution; }

    void SaveDeclarations(wxXmlNode *node);
    void SaveItems(wxXmlNode *node);
    bool IntroOn(double introDuration);
    void DrawIntroPage(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Initiates the completion checker class
     */
    void Solve() { mChecker.Solve(); }
    /**
     * Set our Level member function to the level object we made
     * @param level
     */
    void SetLevel(Level* level) { mLevel = level; }

    void SetCorrect(bool correct) { mCorrect= correct; }
    void SetIncorrect(bool incorrect) { mIncorrect= incorrect; }
    void DrawResult(std::shared_ptr<wxGraphicsContext> graphics, std::wstring str);
    /**
     * When a level is completed or level is changed we update what level we are on
     * @param level
     */
    void SetCurrentLevel(int num){mCurrentLevel = num;}

    /**
     * Getter function for current level
     */
    int GetLevel(){return mCurrentLevel;}

    /**
     * Getter function for random number
     * of this game
     * @return
     */
    std::mt19937 &GetRandom() {return mRandom;}

    double CheckSpartyXLoc(double x, Background* background);
    double CheckSpartyYLoc(double y, Background* background);
    bool GetFloatingDigitsState() { return mFloatingDigits; };
    void SetFloatingDigitsState(bool state) { mFloatingDigits = state; };
};

#endif //ACTIONSUDOKU_SUDOKULIB_GAME_H
