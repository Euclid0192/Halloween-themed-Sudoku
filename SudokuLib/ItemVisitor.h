/**
 * @file ItemVisitor.h
 * @author Nam Hai Nguyen
 * @author Joanna Rodriguez Zamarron
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
 * Base visitor class
 */
class ItemVisitor
{
protected:
    ItemVisitor() {};
public:
    virtual ~ItemVisitor() {}
    /**
     * Visit Digit
     * @param digit: digit we are visiting
     */
    virtual void VisitDigit(Digit *digit) {}
    /**
     * Visit Sparty
     * @param sparty: sparty we are visiting
     */
    virtual void VisitSparty(Sparty *sparty) {}
    /**
     * Visit Xray
     * @param xray: xray we are visiting
     */
    virtual void VisitXray(Xray *xray) {}
    /**
     * Visit Background
     * @param background: background we are visiting
    */
    virtual void VisitBackground(Background *background) {}
    /**
     * Visit Container
     * @param container: container we are visiting
    */
    virtual void VisitContainer(Container *container) {}

};

#endif //TARTARUS_SUDOKULIB_ITEMVISITOR_H
