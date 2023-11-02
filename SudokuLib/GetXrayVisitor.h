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
    /// Pointer to the Xray we are looking for
    Xray *mXray;

public:
    /**
     * Get the xray we are having
     * @return pointer to the xray we currently have
     */
    Xray *GetXray() { return mXray; }

    /**
     * Override to visit xray and get its pointer
     * @param xray
     */
    void VisitXray(Xray *xray) override
    {
        mXray = xray;
    }
};

#endif //TARTARUS_SUDOKULIB_GETXRAYVISITOR_H
