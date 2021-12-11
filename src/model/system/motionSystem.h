/**
 * @file motionSystem.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-11
 */

#ifndef __AGE_MOTION_SYSTEM__
#define __AGE_MOTION_SYSTEM__

#include "system.h"

namespace AGE
{

class Registry;

class MotionSystem final : public LogicSystem
{
public:
    MotionSystem(Registry &registry);
    ~MotionSystem() override;
public:
    void onUpdate() override;
};


} // AGE

#endif
