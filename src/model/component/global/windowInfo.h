/**
 * @file windowInfo.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-15
 */

#ifndef __AGE_WINDOW_INFO_GLOBAL_COMPONENT__
#define __AGE_WINDOW_INFO_GLOBAL_COMPONENT__

#include "../component.h"
#include "../../../common/vec2d.h"

namespace AGE
{

/** @brief Global component for storing the information about the current window */
class CWindowInfo : public GlobalComponent
{
public:
    CWindowInfo(vec2d<int> dimension) : dimension {dimension} {}
    ~CWindowInfo() override {}
public:
    vec2d<int> dimension;
};

} // AGE


#endif
