/**
 * @file collidable.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-12
 */

#ifndef __AGE_COLLIDABLE_COMPONENT__
#define __AGE_COLLIDABLE_COMPONENT__

#include "component.h"

namespace AGE
{

class CCollidable : public Component
{
public:
    CCollidable(Entity &entity): Component {entity} {}
    ~CCollidable() override {}
public:
    // BoundingBox box;
    void (*onCollision)(Entity &);
};

} // AGE


#endif
