/**
 * @file SpartyDeclaration.h
 * @author Nam Hai Nguyen
 *
 * Declaration class for Sparty
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_SPARTYDECLARATION_H
#define ACTIONSUDOKU_SUDOKULIB_SPARTYDECLARATION_H

#include "Declaration.h"

/**
 * Declaration class for Sparty
 */
class SpartyDeclaration : public Declaration
{
private:
    ///Determine which one is drawn first
    int mFront = 1;
    ///Mouth pivot angle
    double mMouthAngle;
    ///Mouth Pivot of Sparty
    wxPoint mMouthPivot;
    ///Head Pivot Angle
    double mHeadAngle;
    ///Head Pivot of Sparty
    wxPoint mHeadPivot;
    ///X-offset when moving Sparty
    double mTargetX;
    ///Y-offset when moving Sparty
    double mTargetY;
public:
    SpartyDeclaration() = delete;
    SpartyDeclaration(const SpartyDeclaration &) = delete;
    SpartyDeclaration(Game *game);

    void XmlLoad(wxXmlNode *node) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(DeclarationVisitor *visitor) override
    {
        visitor->VisitSpartyDeclaration(this);
    }
};

#endif //ACTIONSUDOKU_SUDOKULIB_SPARTYDECLARATION_H
