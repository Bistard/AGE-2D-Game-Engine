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
#include "../system/motionSystem.h"
#include "../system/collisionSystem.h"
#include "../system/renderSystem.h"

namespace AGE
{

template<typename T>
class vec2d;

class BoardWindow : public WindowWithCamera
{
public:
    BoardWindow(vec2d<int> pos, SIZE width, SIZE height): 
        WindowModel {pos, width, height},
        WindowWithCamera {pos, width, height}
    {
        // Constructing `System`s
        Registry &registry = getScene().getRegistry();
        
        getScene().emplaceSystem<MotionSystem>(registry);
        getScene().emplaceSystem<CollisionSystem>(registry);
        getScene().emplaceSystem<RenderSystem>(registry, getWindowBuffer());
    }

    ~BoardWindow() override {}
public:
    // CameraView &addBoardView(std::unique_ptr<CameraView> &&cameraView) 
    // { 
    //     return static_cast<CameraView &>(this->addView(std::move(cameraView))); 
    // }
private:
    // std::unique_ptr<Grid> _grid;
    // bool _boardType;
};

} // AGE


#endif

