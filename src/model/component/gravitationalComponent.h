/**
 * @file gravitationalComponent.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-11
 */

#ifndef __AGE_GRAVITATIONAL_COMPONENT__
#define __AGE_GRAVITATIONAL_COMPONENT__

#include "component.h"
#include "../../common/vec2d.h"

namespace AGE
{

class CGravitational : public Component
{
public:
    CGravitational(Entity &entity, float x, float y): Component {entity}, velocity {x, y} {}
    ~CGravitational() override {}
public:
    vec2d<float> velocity;
};

} // AGE


#endif
