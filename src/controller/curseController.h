/*******************************************************************************
 * @file curseController.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-11-27
 ******************************************************************************/

#ifndef __AGE_CURSE_CONTROLLER__
#define __AGE_CURSE_CONTROLLER__

#include <iostream>
#include "controller.h"

namespace AGE
{

class CurseController : public Controller
{
public:
    CurseController(int FPS): Controller {FPS}
    {
        Ncurses::init(Ncurses::WindowOpt::CBREAK, false);
        Ncurses::setInputTimeout(1 / FPS);
    }
    ~CurseController() { Ncurses::destroy(); }
private:
    int __input() const override { return getch(); }
};

} // AGE  

#endif
