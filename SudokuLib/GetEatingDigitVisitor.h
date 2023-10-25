/**
 * @file GetEatingDigitVisitor.h
 * @author Nam Hai Nguyen
 *
 * A Concrete visitor to get digit that is in range of Sparty's eating
 */

#ifndef TARTARUS_SUDOKULIB_GETEATINGDIGITVISITOR_H
#define TARTARUS_SUDOKULIB_GETEATINGDIGITVISITOR_H

#include "Digit.h"
#include "ItemVisitor.h"

/**
 * A Concrete visitor to get digit that is in range of Sparty's eating
 */
class GetEatingDigitVisitor : public ItemVisitor
{
private:
    Digit *mDigit = nullptr;
public:
    /**
     * Get the digit
     * @return digit
     */
    Digit *GetDigit() { return mDigit; };
    void VisitDigit(Digit *digit)
    {
        mDigit = digit;
    }
};

#endif //TARTARUS_SUDOKULIB_GETEATINGDIGITVISITOR_H
