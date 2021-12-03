/**
 * @file view.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.2
 * @date 2021-12-03
 */

#ifndef __AGE_VIEW__
#define __AGE_VIEW__

namespace AGE
{

namespace Ncurses {
    class Window;
}

/*******************************************************************************
 * @brief Abstract Base Class - `View` component in MVC
 ******************************************************************************/
class View
{
public:
    View() = default;
    virtual ~View() = default;
public:
    virtual void draw(Ncurses::Window &win) = 0;
    virtual void update(Ncurses::Window &win) = 0;
};

} // AGE

#endif

