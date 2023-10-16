/**
 * @file Xray.h
 * @author Nam Hai Nguyen
 *
 * A class for the Xray
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_XRAY_H
#define ACTIONSUDOKU_SUDOKULIB_XRAY_H

#include "Item.h"
/**
 * A class for the Xray
 */
class Xray : public Item
{
private:

public:
    Xray(Game *game);
    Xray() = delete;
    Xray(const Xray &) = delete;
};

#endif //ACTIONSUDOKU_SUDOKULIB_XRAY_H
