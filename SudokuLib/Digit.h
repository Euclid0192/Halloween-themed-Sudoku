/**
 * @file Digit.h
 * @author Nam Hai Nguyen
 *
 * The digit in the sudoku game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_DIGIT_H
#define ACTIONSUDOKU_SUDOKULIB_DIGIT_H

#include "Item.h"

/**
 * The digit in the sudoku game
 */
class Digit : public Item
{
private:
    ///The value of the digit, 0-8
    int mValue;
    ///Determine if this is given or playing digit
    bool mGiven = false;
public:
    Digit() = delete;
    Digit(const Digit &);
    Digit(Game *game);

    void XmlLoadDeclaration(wxXmlNode *node) override;
    std::shared_ptr<Item> Clone() override;
    /**
     * Accept a visitor
     */
    void Accept(ItemVisitor *visitor) { visitor->VisitDigit(this); };
    bool HitTest(int x, int y) override;
};

#endif //ACTIONSUDOKU_SUDOKULIB_DIGIT_H
