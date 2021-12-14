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
    /** @brief Detects colllisions between entities and calls onCollisionFunction
     * for each entity. */
    void onUpdate() override;
};


} // AGE

#endif
