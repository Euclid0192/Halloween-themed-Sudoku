/**
 * @file Digit.h
 * @author Nam Hai Nguyen
 *
 * The digit in the sudoku game
 */

#ifndef TARTARUS_SUDOKULIB_DIGIT_H
#define TARTARUS_SUDOKULIB_DIGIT_H

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
    Digit(const Digit &) = delete;
    Digit(Game *game);

    /**
     * Get the value of the digit
     */
    int GetValue() { return mValue; };

    /**
     * Set the value of the digit
     * @param val: value to be set
     */
    void SetValue(const int &val) { mValue = val; };

    /**
     * Get the given state
     */
    bool GetGiven() { return mGiven; };
    /**
     * Set given state
     * @param state: state to set
     */
    void SetGiven(bool state) { mGiven = state; };
    void XmlLoadDeclaration(wxXmlNode *node) override;
};

#endif //TARTARUS_SUDOKULIB_DIGIT_H
