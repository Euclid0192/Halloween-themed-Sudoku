/**
 * @file IntroPage.h
 * @author yaxuan
 *
 *
 */

#ifndef TARTARUS_SUDOKULIB_INTROPAGE_H
#define TARTARUS_SUDOKULIB_INTROPAGE_H


class IntroPage : wxWindow
{
private:
    wxTimer mDuration;

public:
    IntroPage();
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //TARTARUS_SUDOKULIB_INTROPAGE_H
