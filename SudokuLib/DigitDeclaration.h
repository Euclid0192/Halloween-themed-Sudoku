/**
 * @file DigitDeclaration.h
 * @author Nam Hai Nguyen
 *
 * A class for the declaration of Digit
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_DIGITDECLARATION_H
#define ACTIONSUDOKU_SUDOKULIB_DIGITDECLARATION_H

#include "Declaration.h"

/**
 * A class for the declaration of Digit
 */
class DigitDeclaration : public Declaration
{
private:
    ///The value of the digit, 0-8
    int mValue;
    ///Determine if this is given or playing digit
    bool mGiven = false;
public:
    DigitDeclaration() = delete;
    DigitDeclaration(const DigitDeclaration &) = delete;
    DigitDeclaration(Game *game);

    /**
     * Get the given state
     */
    bool GetGiven() { return mGiven; };
    /**
     * Set given state
     * @param state: state to set
     */
    void SetGiven(bool given) { mGiven = given; };
    void XmlLoad(wxXmlNode *node) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(DeclarationVisitor *visitor) override
    {
        visitor->VisitDigitDeclaration(this);
    }
};

#endif //ACTIONSUDOKU_SUDOKULIB_DIGITDECLARATION_H
