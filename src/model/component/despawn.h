/**
 * @file despawn.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-15
 */

#ifndef __AGE_DESPAWN_COMPONENT__
#define __AGE_DESPAWN_COMPONENT__

#include "component.h"
#include "position.h"
#include "../../utils/math.h"

#define DEFAULT_DESPAWN_TICK 5

namespace AGE
{

/** @brief A marker component to mark if the `Entity` goes out of the screen for
 * over a given ticks. */
class CDespawn : public Component
{
public:
    CDespawn(Entity &entity, CPosition &pos, SIZE tickMax = DEFAULT_DESPAWN_TICK)
        : Component {entity}, pos {pos}, tickMax {tickMax} 
    {}
    ~CDespawn() override {}
public:
    CPosition &pos;
    SIZE count;
    SIZE tickMax;
};

} // AGE


#endif
