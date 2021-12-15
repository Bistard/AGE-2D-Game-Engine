/**
 * @file renderSystem.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-12
 */

#ifndef __AGE_RENDER_SYSTEM__
#define __AGE_RENDER_SYSTEM__

#include "system.h"

namespace AGE
{

namespace Ncurses {
    class WindowBuffer;
}
class Registry;

/**
 * @brief RenderSystem is rendering based on the Painter's Algorithm. It sorts
 * every `Entity` based on their altitude and renders things from the furthest 
 * to the close most.
 */
class RenderSystem final : public ViewSystem
{
public:
    RenderSystem(Registry &registry, Ncurses::WindowBuffer &winBuffer);
    ~RenderSystem() override;
public:
    void onUpdate() override;
private:
    Ncurses::WindowBuffer &_winBuffer;
};

} // AGE

#endif
