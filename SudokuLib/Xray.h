/**
 * @file Xray.h
 * @author Nam Hai Nguyen
 *
 * A class for the Xray
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_XRAY_H
#define ACTIONSUDOKU_SUDOKULIB_XRAY_H

#include "Item.h"
#include<vector>
/**
 * A class for the Xray
 */
class Xray : public Item
{
private:
    ///Maximum number of digits hold
    int mCapacity = 0;
    ///Current number of digits
    int mDigitCount = 0;
    ///Container for digits in Xray
    std::vector<Digit*> mDigits;
public:
    Xray(SudokuGame *game);
    Xray() = delete;
    Xray(const Xray &) = delete;

    void XmlLoadDeclaration(wxXmlNode *node) override;
    /**
     * Accept a visitor
     */
    void Accept(ItemVisitor *visitor) override { visitor->VisitXray(this); };
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    /**
     * Increment digit count by 1
     */
    void IncrementCount() { mDigitCount++; };
    void AddDigit(Digit *digit);
};

#endif //ACTIONSUDOKU_SUDOKULIB_XRAY_H
