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
    ///Whether this has been eaten or not
    bool mEaten = false;

    ///The speed for ghost digit
    double mSpeedX = 25;
    double mSpeedY = 25;

    bool mIsGhost = false;

public:
    Digit() = delete;
    Digit(const Digit &);
    Digit(SudokuGame *game);

    void XmlLoadDeclaration(wxXmlNode *node) override;
    std::shared_ptr<Item> Clone() override;
    /**
     * Get the value of this digit
     * @return int value of digit
     */
    int GetValue() { return mValue; }
    /**
     * Gets the mGiven value whether this is a given or not
     *  @return bool
     */
    bool GetGiven() { return mGiven; }
    /**
     * Get the eaten state
     * @return true if this has been eaten, false otherwise
     */
    bool GetEaten() { return mEaten; }
    /**
     * Set the eaten state of digit
     * @param state : state to set
     */
    void SetEaten(bool state) { mEaten = state; }

    /**
     * Accept a visitor
     */
    void Accept(ItemVisitor *visitor) override { visitor->VisitDigit(this); };
    bool HitTest(double x, double y) override;
    void Update(double elapsed) override;
    bool InBoardRow(double x, double y);
    bool InBoardCol(double x, double y);

    /**
     * Get moving state
     * @return moving state
     */
    bool GetIsGhost() { return mIsGhost; };
    /**
     * Set the state of moving
     * @param isGhost : state to set
     */
    void SetIsGhost(bool isGhost) {
        mIsGhost = isGhost;
    }
    bool InXrayRow(double x, double y);
    bool InXrayCol(double x, double y);
};

#endif //ACTIONSUDOKU_SUDOKULIB_DIGIT_H
