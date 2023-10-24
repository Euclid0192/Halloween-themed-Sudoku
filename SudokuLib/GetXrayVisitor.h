/**
 * @file GetXrayVisitor.h
 * @author Nam Hai Nguyen
 *
 * A concrete visitor to get the Xray of the game
 */

#ifndef TARTARUS_SUDOKULIB_GETXRAYVISITOR_H
#define TARTARUS_SUDOKULIB_GETXRAYVISITOR_H

#include "ItemVisitor.h"
#include "Xray.h"

/**
 * A concrete visitor to get the Xray of the game
 */
class GetXrayVisitor : public ItemVisitor
{
private:
    Xray *mXray;
public:
    Xray *GetXray() { return mXray; }
    void VisitXray(Xray *Xray) override
    {
        mXray = Xray;
    }
};

#endif //TARTARUS_SUDOKULIB_GETXRAYVISITOR_H
