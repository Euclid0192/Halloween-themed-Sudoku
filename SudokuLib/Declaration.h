/**
 * @file Declaration.h
 * @author Nam Hai Nguyen
 *
 * A base class for any declarations in the game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_DECLARATION_H
#define ACTIONSUDOKU_SUDOKULIB_DECLARATION_H

#include "DeclarationVisitor.h"

#include<string>
#include<vector>
#include<map>

class Game;
/**
 * A base class for any declarations in the game
 */
class Declaration
{
private:
    /// The game that this Declaration belongs to
    Game   *mGame;

    ///id of Declaration
    std::wstring mId;

    ///Width and Height
    int mWidth, mHeight;

    ///Image path for this declaration
    std::vector<std::wstring> mImagePaths;

public:
    Declaration(Game *game);
    Declaration() = delete;
    Declaration(const Declaration &) = delete;
    virtual ~Declaration();

    /**
     * Get id of Declaration
     * @return id of Declaration
     */
    std::wstring GetId() { return mId; };
    /**
     * Get image path for this declaration
     * @return image path of the declaration
     */
    std::vector<std::wstring> GetImagePaths() { return mImagePaths; };
    /**
     * Get loaded width
     * @return width in the declaration
     */
    int GetWidth() { return mWidth; };
    /**
     * Get loaded height
     * @return height in the declaration
     */
    int GetHeight() { return mHeight; };
    virtual void XmlLoad(wxXmlNode *node);
    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(DeclarationVisitor *visitor) = 0;
};

#endif //ACTIONSUDOKU_SUDOKULIB_DECLARATION_H
