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
    class Window;
}
class Registry;

class RenderSystem final : public ViewSystem
{
public:
    RenderSystem(Registry &registry, Ncurses::Window &winBuffer);
    ~RenderSystem() override;
public:
    /**
     * @brief Querys all `CRender` components and draws its `CTexture` onto the
     * window buffer by coressponding `CPosition`.
     */
    void onUpdate() override;
private:
    Ncurses::Window &_winBuffer;
};

} // AGE

#endif
