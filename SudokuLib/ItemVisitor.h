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
class Background;
class Container;
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
    /**
     * Visit Background
    */
    virtual void VisitBackground(Background *background) {}
    /**
     * Visit Container
    */
    virtual void VisitContainer(Container *container) {}
};

#endif //TARTARUS_SUDOKULIB_ITEMVISITOR_H
