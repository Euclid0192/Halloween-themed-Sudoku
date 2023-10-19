/**
 * @file ItemVisitor.h
 * @author Nam Hai Nguyen
 *
 * Base visitor
 */

#ifndef TARTARUS_SUDOKULIB_ITEMVISITOR_H
#define TARTARUS_SUDOKULIB_ITEMVISITOR_H

class Sparty;
class Digit;
class Xray;
/**
 * Base visitor
 */
class ItemVisitor
{
protected:
    ItemVisitor() {};
public:
    virtual ~ItemVisitor() {}
    /**
     * Visit Digit
     */
    virtual void VisitDigit(Digit *digit) {}
    /**
     * Visit Sparty
     */
    virtual void VisitSparty(Sparty *sparty) {}
    /**
     * Visit Xray
     */
    virtual void VisitXray(Xray *xray) {}
};

#endif //TARTARUS_SUDOKULIB_ITEMVISITOR_H
