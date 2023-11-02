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
    Background* mBackground = nullptr;

    int mHeight = 0;
    int mWidth = 0;
public:
    Background* GetBackground() { return mBackground; }

    void VisitBackground(Background *background) override {
        if (background->GetBackgroundHeight() > mHeight && background->GetBackgroundWidth() > mWidth){
            mHeight = background->GetBackgroundHeight();
            mWidth = background->GetBackgroundWidth();
            mBackground = background;
        }

    }

};

#endif //TARTARUS_SUDOKULIB_GETBACKGROUNDVISITOR_H
