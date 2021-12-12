/**
 * @file motionSystem.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.2
 * @date 2021-12-12
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
    /**
     * @brief MotionSystem updates all the velocity and gravity for each `Entity`.
     */
    void onUpdate() override;
};


} // AGE

#endif
