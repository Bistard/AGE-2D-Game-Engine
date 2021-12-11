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

// static inline ComponentID getComponentUUID()
// {
//     return static_cast<ComponentID>(UUID {});
// }

// template<typename T>
// inline ComponentID getComponentUUID() noexcept
// {
//     static ComponentID componentTypeID = getComponentUUID();
//     return componentTypeID;
// }

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
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
public:
    Entity &entity;
};

} // AGE


#endif
