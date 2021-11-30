/**
 * @file cameraView.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.2
 * @date 2021-11-30
 */

#ifndef __AGE_BOARD_VIEW__
#define __AGE_BOARD_VIEW__

#include <memory>
#include "view.h"

namespace AGE
{

namespace Ncurses {
    class Window;
};

class WindowWithCamera;

/*******************************************************************************
 * @brief Concrete Derived Class - for Ncurses
 ******************************************************************************/
class CameraView : public View
{
public:
    CameraView(const WindowWithCamera &model): View {}, _model {model} {}
    ~CameraView() override {}
public:
    void draw() override 
    {
        
    }
    void update() override 
    {
        // TODO: draw the Grid to the Ncurses::Window
    }
private:
    // the screen output
    std::unique_ptr<Ncurses::Window> _window;
    // the reference to the `WindowWithCamera`
    const WindowWithCamera &_model;
};

} // AGE

#endif
