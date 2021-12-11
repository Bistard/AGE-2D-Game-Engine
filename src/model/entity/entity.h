/**
 * @file entity.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-10
 */

#ifndef __AGE_ENTITY__
#define __AGE_ENTITY__

#include <vector>
#include <bitset>
#include <memory>

#include "../../utils/uuid.h"

namespace AGE
{

/** @brief the maximum number of components for each entity to have */
constexpr const std::size_t MAX_COMPONENTS = 32;

class Registry;
class Component;
using EntityID = UUID;

/**
 * @brief Class - an `Entity` is composed with mutiple `Component`.
 * 
 * Each construction of `Entity` will be assigned to a UUID. Each `Component`
 * will have the same lifetime as their `Entity`. However, the outside may have
 * access to the `Component` data.
 * 
 * @warning `Entity` may only have one `Component` for each type. For instance, 
 * `Entity` may NOT have two `CVelocity` types. Adding an existed `Component`
 * may results in undefined behavior.
 * 
 * An `Entity` cannot be inherited. An `Entity` can only be created through 
 * `Registry::create()`.
 */
class Entity final
{

private:
    friend class Registry;

    /** @brief constructors */
    Entity(Registry &registry);

public:

    /** @brief DELETED copy constructor */
    Entity(const Entity &other) = delete;
    
    /** @brief Default move constructor */
    Entity(Entity &&other) = default;

    virtual ~Entity();

public:

    /** @brief returns the EntityID (UUID) */
    const EntityID getUUID() const noexcept;
    
    /** @brief determines whether the `Entity` is invalid or not (destroyed) */
    bool isActive() const noexcept;
    
    /** @brief marks this `Entity` as destroyed */
    void destroy() noexcept;
    
    /** @brief returns the reference to where this `Entity` is registered. */
    Registry &getRegistry();

    // FIX: circling include happens
    // /**
    //  * @brief The Following methods are simply wrappers for the `Registry` API's.
    //  * It gives oppotunity to just pass a single `Entity` type into the a
    //  * function and complete the same job as passing `Registry`.
    //  */

    // /** @brief see document `Registry::emplace()` */
    // template<typename ComponentType, typename... Args>
    // [[maybe_unused]] auto &addComponent(Entity &entity, Args &&...args)
    // {
    //     return _registry.emplace<ComponentType, Args>(entity, std::forward<Args>(args)...);
    // }

    // /** @brief see document `Registry::has()` */
    // template<typename ComponentType>
    // bool hasComponent(const Entity &entity) const
    // {
    //     return _registry.has<ComponentType>(entity);
    // }

    // /** @brief see document `Registry::get()` */
    // template<typename ComponentType> 
    // [[nodiscard]] ComponentType &get(Entity entity) const
    // {
    //     return _registry.get<ComponentType>(entity);
    // }

private:

    /** @brief the unique id */
    const UUID _uuid;
    /** @brief marks `Entity` if get destroyed */
    bool _active = true;

    Registry &_registry;
    
    /** @brief tells which `Component` this `Entity` obtains */
    std::bitset<MAX_COMPONENTS> _componentBitset;
    /** @brief stores the actual `Component` Data */
    std::vector<std::unique_ptr<Component>> _components;
};

} // AGE


#endif
