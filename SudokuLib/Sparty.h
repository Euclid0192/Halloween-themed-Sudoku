/**
 * @file Sparty.h
 * @author Nam Hai Nguyen
 *
 * The moving Sparty, main character of the game
 */

#ifndef TARTARUS_SUDOKULIB_SPARTY_H
#define TARTARUS_SUDOKULIB_SPARTY_H

#include "Item.h"

#include<string>
#include<memory>

///Struct type pivot for mouth pivot and head pivot
struct Pivot {
    double angle = 0;
    int x = 0;
    int y = 0;
};
/**
 * The main character of the game
 */
class Sparty : public Item
{
private:
    ///Images of Sparty
    std::unique_ptr<wxImage> mImage1, mImage2;
    ///Bitmaps of Sparty
    std::unique_ptr<wxBitmap> mBitmap1, mBitmap2;
    ///Determine which one is drawn first
    int mFront = 1;
    ///Mouth Pivot of Sparty
    Pivot mMouthPivot;
    ///Head Pivot of Sparty
    Pivot mHeadPivot;
    ///X-offset when moving Sparty
    double mTargetX;
    ///Y-offset when moving Sparty
    double mTargetY;
    ///Speed in X direction
    double mSpeedX;
    ///Speed in Y direction
    double mSpeedY;
public:
    Sparty() = delete;
    Sparty(const Sparty &) = delete;
    Sparty(Game *game);

    void Draw(wxDC *dc) override;
    void XmlLoadDeclaration(wxXmlNode *node) override;

    void SetPivot(Pivot &pivot, double angle, int x, int y);
};


#endif //TARTARUS_SUDOKULIB_SPARTY_H
