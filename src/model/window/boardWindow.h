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
        
        getScene().emplaceLogicSystem<MotionSystem>(registry);
        getScene().emplaceLogicSystem<CollisionSystem>(registry);
        getScene().emplaceViewSystem<RenderSystem>(registry, getWindowBuffer());
    }

    ~BoardWindow() override {}
};

} // AGE


#endif

