/**
 * @file boardWindow.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief one of default WindowModel provied by the AGE engine.
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __AGE_BOARD_WINDOW__
#define __AGE_BOARD_WINDOW__

#include "windowModel.h"
#include "../../view/cameraView.h"

namespace AGE
{

template<typename T>
class Point;

class BoardWindow : public WindowWithCamera
{
public:
    BoardWindow(Point<int> pos, SIZE width, SIZE height): 
        WindowModel {pos, width, height},
        WindowWithCamera {pos, width, height}
    {}
    ~BoardWindow() override {}
public:
    CameraView &addBoardView(std::unique_ptr<CameraView> &&cameraView) 
    { 
        return static_cast<CameraView &>(this->addView(std::move(cameraView))); 
    }
private:
    // std::unique_ptr<Grid> _grid;
    // bool _boardType;
};

} // AGE


#endif

