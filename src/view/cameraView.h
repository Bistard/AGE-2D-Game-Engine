/**
 * @file cameraView.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.3
 * @date 2021-12-03
 */

#ifndef __AGE_BOARD_VIEW__
#define __AGE_BOARD_VIEW__

#include <memory>
#include <queue>

#include "view.h"
#include "../model/window/windowModel.h"

namespace AGE
{

namespace Ncurses {
    class Window;
}

/*******************************************************************************
 * @brief Concrete Derived Class - for Ncurses
 ******************************************************************************/
class CameraView : public View
{
public:
    CameraView(WindowWithCamera &model);
    ~CameraView() override;
public:
    void draw(Ncurses::Window &win) override;
    void update(Ncurses::Window &win) override;
private:
    // the reference to the `WindowWithCamera`
    const WindowWithCamera &_model;
};

} // AGE

#endif
