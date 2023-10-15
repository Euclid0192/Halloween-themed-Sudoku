/**
 * @file Xray.h
 * @author Nam Hai Nguyen
 *
 * A class for the Xray
 */

#ifndef TARTARUS_SUDOKULIB_XRAY_H
#define TARTARUS_SUDOKULIB_XRAY_H

#include "Item.h"
/**
 * A class for the Xray
 */
class Xray : public Item
{
private:
    ///Maximum number of digits hold
    int mCapacity = 0;
public:
    Xray(Game *game);
    Xray() = delete;
    Xray(const Xray &) = delete;

    void XmlLoadDeclaration(wxXmlNode *node) override;
};

#endif //TARTARUS_SUDOKULIB_XRAY_H
