/**
 * @file statusWindow.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief one of default WindowModel provied by the AGE engine.
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __AGE_STATUS_WINDOW__
#define __AGE_STATUS_WINDOW__

#include "windowModel.h"
#include "../system/renderSystem.h"

namespace AGE
{

class StatusWindow : public WindowWithCamera
{
public:
    StatusWindow(vec2d<int> pos, SIZE width, SIZE height): 
        WindowModel {pos, width, height},
        WindowWithCamera {pos, width, height}
    {
        // Constructing `System`s
        Registry &registry = getScene().getRegistry();
        getScene().emplaceViewSystem<RenderSystem>(registry, getWindowBuffer());
    }
    ~StatusWindow() override {}
};

} // AGE


#endif
