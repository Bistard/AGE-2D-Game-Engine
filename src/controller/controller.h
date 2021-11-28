/*******************************************************************************
 * @file controller.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.2
 * @date 2021-11-28
 ******************************************************************************/

#ifndef __AGE_CONTROLLER__
#define __AGE_CONTROLLER__

#include "adapter/ncurseAdapter.h"

class WindowModel;

namespace AGE
{

/*******************************************************************************
 * @brief abstract base class
 ******************************************************************************/
class Controller 
{
public:
    Controller(int FPS): _fps {FPS} {}
    ~Controller() = default;
public:
    void setFPS(int FPS) { _fps = FPS; }
    int getInput() const { return __input(); }
private:
    virtual int __input() const = 0;
protected:
    int _fps;
};

} // AGE

#endif
