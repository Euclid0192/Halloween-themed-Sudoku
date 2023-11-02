/**
 * @file GetBackgroundVisitor.h
 * @author anamo
 *
 *
 */

#ifndef TARTARUS_SUDOKULIB_GETBACKGROUNDVISITOR_H
#define TARTARUS_SUDOKULIB_GETBACKGROUNDVISITOR_H

#include "ItemVisitor.h"
#include "Background.h"

/**
*  Visitor to get background
*/
class GetBackgroundVisitor : public ItemVisitor
{
private:
    /// Background we are looking for
    Background* mBackground = nullptr;
    /// Height we weill compare to get the biggest background
    int mHeight = 0;
    /// Width we weill compare to get the biggest background
    int mWidth = 0;
public:
    /**
    * Gets us the background we just found
    * @return background
    */
    Background* GetBackground() { return mBackground; }
    /**
     * Checks if we are getting the background that is larger
     * @param background
     */
    void VisitBackground(Background *background) override {
        if (background->GetBackgroundHeight() > mHeight && background->GetBackgroundWidth() > mWidth){
            mHeight = background->GetBackgroundHeight();
            mWidth = background->GetBackgroundWidth();
            mBackground = background;
        }

    }

};

#endif //TARTARUS_SUDOKULIB_GETBACKGROUNDVISITOR_H
