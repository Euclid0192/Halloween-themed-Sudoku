/**
 * @file Sparty.h
 * @author Nam Hai Nguyen
 *
 * The moving Sparty, main character of the game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_SPARTY_H
#define ACTIONSUDOKU_SUDOKULIB_SPARTY_H

#include "Item.h"

#include<string>
#include<memory>

/**
 * The main character of the game
 */
class Sparty : public Item
{
private:
    ///Images of Sparty
    std::unique_ptr<wxImage> mImage1, mImage2;
    ///Bitmaps of Sparty
    wxGraphicsBitmap mBitmap1, mBitmap2;
    ///Speed in X direction
    double mSpeedX;
    ///Speed in Y direction
    double mSpeedY;
    ///Determine which one is drawn first
    int mFront = 1;
    ///Mouth pivot angle
    double mMouthAngle;
    ///Mouth Pivot of Sparty
    wxPoint mMouthPivot;
    ///Head Pivot Angle
    double mHeadAngle;
    ///Head Pivot of Sparty
    wxPoint mHeadPivot;
    ///X-offset when moving Sparty
    double mTargetX;
    ///Y-offset when moving Sparty
    double mTargetY;
    ///Distance that we need to travel
    double mDistance;
    ///Distance that we have travel
    double mTraveled = 0;
    ///Determine when to update
    bool mUpdate = false;
public:
    Sparty() = delete;
    Sparty(const Sparty &) = delete;
    Sparty(Game *game);

    /**
     * Set the update state
     * @param state : state to be set
     */
    void SetUpdateState(bool state) { mUpdate = state;};
    /**
     * Get the offset to the target in X direction
     * @return offset in X direction
     */
    double GetTargetX() { return mTargetX; };
    /**
     * Get the offset to the target in Y direction
     * @return offset in Y direction
     */
    double GetTargetY() { return mTargetY; };
    /**
     * Get the maximum speed
     */
    double GetMaxSpeed();
    /**
     * Set the speed in X direction
     * @param x : speed in X direction
     */
    void SetSpeedX(double x) { mSpeedX = x; };
    /**
     * Set the speed in Y direction
     * @param y : speed in Y direction
     */
    void SetSpeedY(double y) { mSpeedY = y; };
    /**
     * Set the distance left needed to move
     * @param x : distance in X direction
     * @param y : distance in Y direction
     */
    void SetDistance(double distance) { mDistance = distance; };
    void SetTraveled(double traveled) { mTraveled = traveled; };

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoadDeclaration(wxXmlNode *node) override;
    void Update(double elapsed) override;
    /**
     * Accept a visitor
     */
    void Accept(ItemVisitor *visitor) { visitor->VisitSparty(this); };
};

#endif //ACTIONSUDOKU_SUDOKULIB_SPARTY_H
