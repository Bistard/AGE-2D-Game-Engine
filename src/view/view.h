/**
 * @file view.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __AGE_VIEW__
#define __AGE_VIEW__

namespace AGE
{

/*******************************************************************************
 * @brief Abstract Base Class - `View` component in MVC
 ******************************************************************************/
class View
{
public:
    View() = default;
    virtual ~View() = default;
public:
    virtual void draw() = 0;
    virtual void update() = 0;
};

} // AGE

#endif

