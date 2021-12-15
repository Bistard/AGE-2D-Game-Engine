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
#include "boundingBox.h"

namespace AGE
{

using onCollisionFunc = void (*)(Entity &, Entity &);

class CCollidable : public Component
{
public:
    CCollidable(Entity &entity, CBoundingBox &box, onCollisionFunc onCollision = [](Entity &self, Entity &other) {})
        : Component {entity}, box {box}, onCollision {onCollision} 
    {}
    ~CCollidable() override {}
public:
    CBoundingBox &box;
    onCollisionFunc onCollision;
};

} // AGE


#endif
