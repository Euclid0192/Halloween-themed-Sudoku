/**
 * @file SetGivenVisitor.h
 * @author Nam Hai Nguyen
 *
 * A concrete visitor to make a digit given when loading declaration
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_SETGIVENVISITOR_H
#define ACTIONSUDOKU_SUDOKULIB_SETGIVENVISITOR_H

#include "DeclarationVisitor.h"
#include "DigitDeclaration.h"

/**
 * A concrete visitor to make a digit given when loading declaration
 */
class SetGivenVisitor : public DeclarationVisitor
{
private:

public:
    void VisitDigitDeclaration(DigitDeclaration *digit) override
    {
        digit->SetGiven(true);
    }
};

#endif //ACTIONSUDOKU_SUDOKULIB_SETGIVENVISITOR_H
