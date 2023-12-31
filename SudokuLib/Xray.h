/**
 * @file Xray.h
 * @author Nam Hai Nguyen
 *
 * A class for the Xray
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_XRAY_H
#define ACTIONSUDOKU_SUDOKULIB_XRAY_H

#include "Item.h"
#include "SudokuGame.h"
#include<vector>
/**
 * A class for the Xray
 */
class Xray : public Item
{
private:
    ///Maximum number of digits hold
    int mCapacity = 0;
    ///Container for digits in Xray
    std::vector<Digit*> mDigits;

    ///Logic to make digit not overlapping
    /// Current X location in xray
    int mCurX = 0;
    /// Current Y location in xray
    int mCurY = 0;
public:
    Xray(SudokuGame *game);
    Xray() = delete;
    Xray(const Xray &) = delete;

    void XmlLoadDeclaration(wxXmlNode *node) override;

    /**
     * Accept a visitor
     * @param visitor : visitor to be accepted
     */
    void Accept(ItemVisitor *visitor) override { visitor->VisitXray(this); };
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void AddDigit(Digit *digit);
    void Relocate(Digit *digit);
    void Spit(int row, int col, int value);
    void Remove(Digit *digit);
};

#endif //ACTIONSUDOKU_SUDOKULIB_XRAY_H
