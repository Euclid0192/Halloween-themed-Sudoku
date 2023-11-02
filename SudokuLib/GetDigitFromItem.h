/**
 * @file GetDigitFromItem.h
 * @author Nam Hai Nguyen
 *
 * A Concrete visitor to get digit that is in range of Sparty's eating
 */

#ifndef TARTARUS_SUDOKULIB_GETDIGITFROMITEM_H
#define TARTARUS_SUDOKULIB_GETDIGITFROMITEM_H

#include "Digit.h"
#include "ItemVisitor.h"

/**
 * A Concrete visitor to get digit that is in range of Sparty's eating
 */
class GetDigitFromItem : public ItemVisitor
{
private:
    ///Pointer to the digit we are looking for
    Digit *mDigit = nullptr;
public:
    /**
     * Get the digit
     * @return digit
     */
    Digit *GetDigit() { return mDigit; };
    /**
     * Override to visit digits
     * @param digit : digit we are visiting
     */
    void VisitDigit(Digit *digit)
    {
        mDigit = digit;
    }
};

#endif //TARTARUS_SUDOKULIB_GETDIGITFROMITEM_H
