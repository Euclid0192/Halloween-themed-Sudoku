/**
 * @file Game.h
 * @author Nam Hai Nguyen
 *
 * Class that implements a sudoku game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_GAME_H
#define ACTIONSUDOKU_SUDOKULIB_GAME_H

#include "Item.h"
#include "Declaration.h"

#include "Level.h"
#include<string>
#include<map>
#include<memory>
#include<vector>

class Game
{
private:
    ///All items in the Declarations
    std::map<std::wstring, std::shared_ptr<Declaration>> mDeclarations;
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

    void OnLeftDown(int x, int y);
public:
    Game();
    /**
     * Destructor
     */
    virtual ~Game() = default;

    void AddDeclaration(std::shared_ptr<Declaration> declaration);
    void AddItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> HitTest(int x, int y);
    void MoveToFront(std::shared_ptr<Item> item);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    //void Load(const wxString &filename);
//    void XmlDeclaration(wxXmlNode *node);
//    void XmlItem(wxXmlNode *node);
    void Clear();

    void Update(double elapsed);

    /**
     * Get the directory the images are stored in
     * @return Images directory path
     */
    const std::wstring &GetImagesDirectory() const { return mImagesDirectory; }
    void SetImagesDirectory(const std::wstring &dir);

    /**
     * Get the declaration of a certain ID
     * @return declaration of item
     */
     std::shared_ptr<Declaration> GetDeclaration(std::wstring* id) { return mDeclarations[*id]; }
};

#endif //ACTIONSUDOKU_SUDOKULIB_GAME_H
