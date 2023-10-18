/**
 * @file BackgroundDeclaration.h
 * @author Lewi Anamo
 *
 *
 */

#ifndef TARTARUS_SUDOKULIB_BACKGROUNDDECLARATION_H
#define TARTARUS_SUDOKULIB_BACKGROUNDDECLARATION_H

#include "Declaration.h"

class BackgroundDeclaration : public Declaration
{
private:

public:
    BackgroundDeclaration(Game *game);
    BackgroundDeclaration() = delete;
    BackgroundDeclaration(const BackgroundDeclaration &) = delete;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(DeclarationVisitor *visitor) override
    {
        visitor->VisitBackgroundDeclaration(this);
    }
};

#endif //TARTARUS_SUDOKULIB_BACKGROUNDDECLARATION_H
