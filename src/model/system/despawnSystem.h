/**
 * @file despawnSystem.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-15
 */

#ifndef __AGE_DESPAWN_SYSSTEM__
#define __AGE_DESPAWN_SYSSTEM__

#include "system.h"

namespace AGE
{

class Registry;

/**
 * @brief DespawnSystem handles all the entities that has `CDespawn` components
 * and check if it goes out the screen for a given ticks.
 */
class DespawnSystem : public LogicSystem
{
public:
    DespawnSystem(Registry &registry);
    ~DespawnSystem() override;
public:
    void onUpdate() override;
};

} // AGE


#endif
