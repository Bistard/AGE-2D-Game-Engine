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

using ComponentUUID = UUID;
using ComponentID = int;

static inline ComponentUUID getComponentUUID()
{
    return static_cast<ComponentUUID>(UUID {});
}

template<typename T>
inline ComponentUUID getComponentUUID() noexcept
{
    static ComponentUUID componentTypeID = getComponentUUID();
    return componentTypeID;
}

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
 * when rendering, we query all `Entity`s which obtain `CPosition` and `CRenderer`. 
 * Instead, we may only querying for `CRenderer` which has a reference to a 
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


/** @brief Base Class - see `Registry` document for further informations. */
class GlobalComponent
{
public:
    GlobalComponent() = default;
    virtual ~GlobalComponent() = default;
};

} // AGE


#endif
