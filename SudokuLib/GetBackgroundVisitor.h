/**
 * @file GetBackgroundVisitor.h
 * @author anamo
 *
 * Visitor for the Background class
 */

#ifndef TARTARUS_SUDOKULIB_GETBACKGROUNDVISITOR_H
#define TARTARUS_SUDOKULIB_GETBACKGROUNDVISITOR_H

#include "ItemVisitor.h"
#include "Background.h"

/**
 * Visitor for the Background class
 */
class GetBackgroundVisitor : public ItemVisitor
{
private:
    ///Background we need to find
    Background* mBackground = nullptr;
    ///Height of background
    int mHeight = 0;
    ///Width of background
    int mWidth = 0;
public:
    /**
     * Get the background
     * @return pointer to this background
     */
    Background* GetBackground() { return mBackground; }
    /**
     * Override function to visit the background
     * @param background : background we are visiting
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
