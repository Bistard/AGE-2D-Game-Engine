/**
 * @file border.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-12
 */

#ifndef __AGE_BORDER_GLOBAL_COMPONENT__
#define __AGE_BORDER_GLOBAL_COMPONENT__

#include "component.h"

namespace AGE
{

/** @brief A global component storing data for display border of a window */
class CBorderView : public GlobalComponent
{
public:
    // default value: 32 -> blanks space
    CBorderView(bool visible, int top = 32, int bottom = 32, int left = 32, int right = 32, int corner = 32)
        : GlobalComponent {}, top {top}, bottom {bottom}, left {left}, 
          right {right}, corner {corner} 
    {}
    ~CBorderView() override {}
public:
    bool visible;
    int top, bottom, left, right, corner;
};

} // AGE


#endif
