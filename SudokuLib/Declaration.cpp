/**
 * @file Declaration.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Declaration
 */

#include "pch.h"
#include "Declaration.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 * @param game: the game that this Declaration is a member of
 */
Declaration::Declaration(Game *game): mGame(game)
{

}

/**
 * Destructor
 */
Declaration::~Declaration()
{
}

/**
 * Load the attributes for an Declaration node in the declaration.
 *
 * This is the  base class version that loads the attributes
 * common to all Declarations. Override this to load custom attributes
 * for specific Declarations.
 *
 * @param node The Xml node we are loading the Declaration from
 */
void Declaration::XmlLoad(wxXmlNode *node)
{
    ///Load id
    mId = node->GetAttribute(L"id", L"").ToStdWstring();

    ///Load width and height
    long width, height;
    node->GetAttribute(L"width", L"0").ToLong(&width);
    node->GetAttribute(L"height", L"0").ToLong(&height);

    mWidth = (int)width;
    mHeight = (int)height;
    ///Load image path
    wstring imagePath = node->GetAttribute(L"image", L"").ToStdWstring();
    ///If it has attribute image, it is all items except Sparty
    if (imagePath != L"")
    {
        mImagePaths.push_back(imagePath);
    }
        ///Only Sparty has image1, image2 instead of image
    else
    {
        ///Load images' paths
        wstring SpartyDeclarationImage1 = node->GetAttribute(L"image1", L"").ToStdWstring();
        wstring SpartyDeclarationImage2 = node->GetAttribute(L"image2", L"").ToStdWstring();
        mImagePaths.push_back(SpartyDeclarationImage1);
        mImagePaths.push_back(SpartyDeclarationImage2);
    }
}


