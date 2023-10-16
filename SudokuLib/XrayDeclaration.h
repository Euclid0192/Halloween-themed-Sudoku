/**
 * @file XrayDeclaration.h
 * @author Nam Hai Nguyen
 *
 * A class for the Declaration of Xray
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_XRAYDECLARATION_H
#define ACTIONSUDOKU_SUDOKULIB_XRAYDECLARATION_H

#include "Declaration.h"
/**
 * A class for the Declaration of Xray
 */
class XrayDeclaration : public Declaration
{
private:
    ///Maximum number of digits hold
    int mCapacity = 0;
public:
    XrayDeclaration(Game *game);
    XrayDeclaration() = delete;
    XrayDeclaration(const XrayDeclaration &) = delete;

    void XmlLoad(wxXmlNode *node) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(DeclarationVisitor *visitor) override
    {
        visitor->VisitXrayDeclaration(this);
    }
};

#endif //ACTIONSUDOKU_SUDOKULIB_XRAYDECLARATION_H
