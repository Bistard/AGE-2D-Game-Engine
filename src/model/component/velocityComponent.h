/**
 * @file velocityComponent.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-10
 */

#ifndef __AGE_VELOCITY_COMPONENT__
#define __AGE_VELOCITY_COMPONENT__

#include "component.h"
#include "../../common/vec2d.h"

namespace AGE
{

class CVelocity : public Component
{
public:
    CVelocity(Entity &entity, float x, float y): Component {entity}, velocity {x, y} {}
    ~CVelocity() override {}
public:
    vec2d<float> velocity;
};

} // AGE


#endif
