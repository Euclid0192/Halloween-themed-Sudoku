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
	char mKeyPressed;
	bool mKeyInXRay = false;


public:
    Xray *GetXray() { return mXray; }
	void SetKeyPressed(char key) { mKeyPressed = key; }

    void VisitXray(Xray *xray) override
    {
		if (xray->HasKey(mKeyPressed))
		{
			mKeyInXRay = true;
		}

        mXray = xray;
    }
};

#endif //TARTARUS_SUDOKULIB_GETXRAYVISITOR_H
