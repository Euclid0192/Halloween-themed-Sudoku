/**
 * @file GetSpartyVisitor.h
 * @author Nam Hai Nguyen
 *
 * A concrete visitor to get the sparty of the game
 */

#ifndef TARTARUS_SUDOKULIB_GETSPARTYVISITOR_H
#define TARTARUS_SUDOKULIB_GETSPARTYVISITOR_H

#include "ItemVisitor.h"
#include "Sparty.h"

/**
 * A concrete visitor to get the sparty of the game
 */
class GetSpartyVisitor : public ItemVisitor
{
private:
    ///Pointer to the Sparty we are looking for
    Sparty *mSparty = nullptr;
public:
    /**
     * Get the pointer to the sparty
     * @return pointer to the sparty
     */
    Sparty *GetSparty() { return mSparty; }

    /**
     * Override function to visit the sparty and get its pointer
     * @param sparty : the sparty we are visiting
     */
    void VisitSparty(Sparty *sparty) override
    {
        mSparty = sparty;
    }
};

#endif //TARTARUS_SUDOKULIB_GETSPARTYVISITOR_H
