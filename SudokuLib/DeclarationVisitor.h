/**
 * @file DeclarationVisitor.h
 * @author Nam Hai Nguyhe
 *
 * A base visitor to visit any declaration
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_DECLARATIONVISITOR_H
#define ACTIONSUDOKU_SUDOKULIB_DECLARATIONVISITOR_H

class DigitDeclaration;
class SpartyDeclaration;
class XrayDeclaration;
class BackgroundDeclaration;

class DeclarationVisitor
{
protected:
    DeclarationVisitor() {}
public:
    virtual ~DeclarationVisitor() {}
    /**
     * Visit Digit Declaration
     */
    virtual void VisitDigitDeclaration(DigitDeclaration *digit) {}
    /**
     * Visit Sparty Declaration
     */
    virtual void VisitSpartyDeclaration(SpartyDeclaration *sparty) {}
    /**
     * Visit Xray
     */
    virtual void VisitXrayDeclaration(XrayDeclaration *xray) {}
    /**
     * Visit Background
     */
     virtual  void VisitBackgroundDeclaration(BackgroundDeclaration *background) {}
};

#endif //ACTIONSUDOKU_SUDOKULIB_DECLARATIONVISITOR_H
