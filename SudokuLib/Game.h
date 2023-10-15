/**
 * @file Game.h
 * @author Nam Hai Nguyen
 *
 * Class that implements a sudoku game
 */

#ifndef TARTARUS_SUDOKULIB_GAME_H
#define TARTARUS_SUDOKULIB_GAME_H

#include "Item.h"

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
public:
    Game();
    /**
     * Destructor
     */
    virtual ~Game() = default;

    void AddDeclaration(std::shared_ptr<Item> item);
    void AddItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> HitTest(int x, int y);
    void MoveToFront(std::shared_ptr<Item> item);

    void OnDraw(wxDC *graphics);

    void Load(const wxString &filename);
    void XmlDeclaration(wxXmlNode *node);
    void XmlItem(wxXmlNode *node);
    void Clear();

    void Update(double elapsed);

    /**
     * Get the directory the images are stored in
     * @return Images directory path
     */
    const std::wstring &GetImagesDirectory() const { return mImagesDirectory; }
    void SetImagesDirectory(const std::wstring &dir);

};

#endif //TARTARUS_SUDOKULIB_GAME_H
