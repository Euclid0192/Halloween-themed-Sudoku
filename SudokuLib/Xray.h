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
    ///Maximum number of digits hold
    int mCapacity = 0;
public:
    Xray(Game *game);
    Xray() = delete;
    Xray(const Xray &) = delete;

    void XmlLoadDeclaration(wxXmlNode *node) override;
    /**
     * Accept a visitor
     */
    void Accept(ItemVisitor *visitor) override { visitor->VisitXray(this); };
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //ACTIONSUDOKU_SUDOKULIB_XRAY_H
