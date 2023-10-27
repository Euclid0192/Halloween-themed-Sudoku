/**
 * @file Sparty.h
 * @author Nam Hai Nguyen
 *
 * The moving Sparty, main character of the game
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_SPARTY_H
#define ACTIONSUDOKU_SUDOKULIB_SPARTY_H

#include "Item.h"
#include "Xray.h"

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
    ///Speed
    wxPoint2DDouble mSpeed;
    ///Determine which one is drawn first
    int mFront = 1;
    ///Mouth pivot angle
    double mMouthAngle;
    ///Mouth Pivot of Sparty
    wxPoint mMouthPivot;
    ///Head Pivot max Angle
    double mHeadAngle;
    ///Head Pivot of Sparty
    wxPoint mHeadPivot;

	/// Determine if sparty headbutt
	bool mHeadButt = false;
	/// Use to calculate the headbutt time
	double mHeadButtTimeUpdate = 0;
    ///Head Pivot Angle current
    double mHeadAngleUpdate;

    ///X-offset when moving Sparty
    double mTargetX;
    ///Y-offset when moving Sparty
    double mTargetY;
    ///Distance that we need to travel
    double mDistance;
    ///Distance that we have travel
    double mTraveled = 0;
    ///Determine when to move
    bool mMove = false;

    ///Determine when to open mouth for eating
    bool mEat = false;
    ///Determine when to open mouth for spitting
    bool mSpit = false;
    ///Eating time
    double mEatTime = 0;
    ///Current head angle to make animation smooth
    double mMouthAngleUpdate;
    ///The Xray of the game to handle eating
    Xray *mXray = nullptr;
public:
    Sparty() = delete;
    Sparty(const Sparty &) = delete;
    Sparty(SudokuGame *game);

    /**
     * Set the move state
     * @param state : state to be set
     */
    void SetMoveState(bool state) { mMove = state;};

    /**
     * Set the eat state
     * @param state : state to be set
     */
    void SetEatState(bool state) { mEat = state;};
    /**
     * Set the spit state
     * @param state : state to be set
     */
    void SetSpitState(bool state) { mSpit = state;};
	/**
	 * Set the headbutt state
	 * @param state : state to be set
	 */
	void SetHeadButtState(bool state ) {mHeadButt = state;}
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
     * Set the moving speed
     * @param speed : speed to be set
     */
    void SetSpeed(wxPoint2DDouble speed) { mSpeed = speed;};
    /**
     * Set the distance left needed to move
     * @param x : distance in X direction
     * @param y : distance in Y direction
     */
    void SetDistance(double distance) { mDistance = distance; };
    /**
     * Set the distance we have travelled
     * @param traveled : distance we have traveled
     */
    void SetTraveled(double traveled) { mTraveled = traveled; };
    void MoveAction(double elapsed);
    void EatAction(double elapsed);
    void StartMouthTimer();
    /**
     * Set the xray of this sparty
     * @param xray : the associated Xray
     */
    void SetXray(Xray *xray) { mXray = xray; };
	void StartHeadButtTimer();
	void HeadButtAction(double elapsed);


    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoadDeclaration(wxXmlNode *node) override;
    void Update(double elapsed) override;

    /**
     * Accept a visitor
     */
    void Accept(ItemVisitor *visitor) override { visitor->VisitSparty(this); };

};

#endif //ACTIONSUDOKU_SUDOKULIB_SPARTY_H
