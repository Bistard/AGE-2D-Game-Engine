/**
 * @file collisionSystem.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-11
 */

#ifndef __AGE_COLLISION_SYSTEM__
#define __AGE_COLLISION_SYSTEM__

#include "system.h"

namespace AGE
{

class Registry;

class CollisionSystem final : public LogicSystem
{
public:
    CollisionSystem(Registry &registry);
    ~CollisionSystem() override;
public:
    void onUpdate() override;
};


} // AGE

#endif
