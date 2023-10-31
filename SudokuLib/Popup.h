/**
 * @file Popup.h
 * @author Nam Hai Nguyen
 *
 * A class for popups in the game
 */

#ifndef TARTARUS_SUDOKULIB_POPUP_H
#define TARTARUS_SUDOKULIB_POPUP_H

#include <string>
#include <memory>
class SudokuGame;
/**
 * A class for popups in the game
 */
class Popup
{
private:
    ///The game that this popup belongs to
    SudokuGame *mGame;
    ///Message in the popup
    std::wstring mMessage;
    ///Determine when to appear
    bool mAppear = false;
    ///Location in the mainframe
    wxPoint2DDouble mLocation;
public:
    Popup(SudokuGame *game);
    Popup() = delete;
    Popup(const Popup &) = delete;
//    virtual ~Popup();

    /**
     * Getter for appearing state
     * @return appearing state
     */
    bool GetAppearState() { return mAppear; };
    /**
     * Setter for appearing state
     * @param state : state to be set
     */
    void SetAppearState(bool state) { mAppear = state; };
    /**
     * Set the location of the item
     * @param x : x coordinate
     * @param y : y coordinate
     */
    void SetLocation(double x, double y) { mLocation.m_x = x; mLocation.m_y = y; };

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void Update(double elapsed);
};

#endif //TARTARUS_SUDOKULIB_POPUP_H
