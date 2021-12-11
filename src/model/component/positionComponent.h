/**
 * @file positionComponent.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-11
 */

#ifndef __AGE_POSITION_COMPONENT__
#define __AGE_POSITION_COMPONENT__

#include "component.h"
#include "../../common/vec2d.h"

namespace AGE
{

class CPosition : public Component
{
public:
    CPosition(Entity &entity, float x, float y): Component {entity}, position {x, y} {}
    ~CPosition() override {}
public:
    vec2d<float> position;
};

} // AGE

#endif
