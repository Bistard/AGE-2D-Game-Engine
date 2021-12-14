/**
 * @file position.h
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

using AltitudeType = uint8_t;
#define TOP_ALTITUDE 255

class CPosition : public Component
{
public:
    CPosition(Entity &entity, float x, float y, AltitudeType altitude)
        : Component {entity}, val {x, y}, altitude {altitude} 
    {}
    ~CPosition() override {}
public:
    vec2d<float> val;
    /** @brief altitude in the drawing */
    AltitudeType altitude;
};

} // AGE

#endif
