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
    Sparty *mSparty;
public:
    Sparty *GetSparty() { return mSparty; }
    void VisitSparty(Sparty *sparty) override
    {
        mSparty = sparty;
    }
};

#endif //TARTARUS_SUDOKULIB_GETSPARTYVISITOR_H
