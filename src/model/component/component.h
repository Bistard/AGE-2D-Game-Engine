/**
 * @file component.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-10
 */

#ifndef __AGE_COMPONENT__
#define __AGE_COMPONENT__

#include <bitset>
#include <array>

#include "../../utils/uuid.h"

namespace AGE
{

class Entity;

using ComponentID = int;

inline int getComponentSequenceID()
{
    static int componentSequenceID = 0;
    return componentSequenceID++;
}

template<typename T>
inline int getComponentSequenceID() noexcept
{
    static int componentSequenceID = getComponentSequenceID();
    return componentSequenceID;
}

/**
 * @brief Base Class - all the `Component` part from Entity-Component 
 * system inherits from here.
 * 
 * `Component` only stores data (logicless). Logic is handled using `System`.
 * `Component` cannot be re-assigned to another `Entity`.
 * 
 * @note `Component` may have reference to the other `Component`s. For instance, 
 * when rendering, we query all `Entity`s which obtain `CPosition` and `CRender`. 
 * Instead, we may only querying for `CRender` which has a reference to a 
 * `CPosition` to slightly increase query speed.
 */
class Component
{
public:
    /** @brief constructor */
    Component(Entity &entity): entity {entity} {}

    /** @brief DELETED copy constructor */
    Component(const Component &other) = delete;
    
    /** @brief Default move constructor */
    Component(Component &&other) = default;

    virtual ~Component() = default;
public:
    Entity &entity;
};

} // AGE


#endif
