/**
 * @file registry.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-09
 */

#ifndef __AGE_REGISTRY__
#define __AGE_REGISTRY__

#include <memory>
#include <unordered_map>
#include <map>
#include <list>
#include <vector>

#include "../entity/entity.h"
#include "../component/component.h"
#include "../../utils/uuid.h"

namespace AGE 
{

/**
 * @brief Entity-Component System (ECS)
 * 
 * The `Registry` is the core class of the ECS framework. It stores `Entity`s 
 * and arranges pools of `Component`s for fast querying.
 */
class Registry 
{
    using EntitieQueryGroup = std::list<Entity *>;
public:

    /** @brief Default constructor. */
    Registry() = default;

    /** @brief Default move constructor. */
    Registry(Registry &&) = default;
    
    /** @brief Default move assignment operator. @return This registry. */
    Registry &operator=(Registry &&) = default;

public:

    /**
     * @brief Creates a new `Entity` inside the `Registry`, then returns it.
     *
     * The newly constructed `Entity` will be assigned with a Universally Unique 
     * Identifier (UUID).
     *
     * @return The `Entity` reference.
     */
    [[nodiscard]] auto &create()
    {
        // constructing `Entity`
        std::unique_ptr<Entity> entity { new Entity {*this} };
        auto &entityRef = *entity;
        _entities.emplace( std::make_pair( entity->getUUID(), std::move(entity) ) );
        return entityRef;
    }

    /** 
     * @brief Returns the number entities registered so far (including inactive 
     * entities) .
     * @return Number of entities.
     */
    [[nodiscard]] std::size_t size() const noexcept 
    {
        return _entities.size();
    }

    /** 
     * @brief Returns the number entities which are still in active.
     * @return Number of entities in active.
     */
    [[nodiscard]] std::size_t active() const noexcept 
    {
        std::size_t sz = 0;
        for (auto &[id, e] : _entities) {
            if (e->_active) ++sz;
        }
        return sz;
    }

    /**
     * @brief Consturcts and assigns a new `Component` to the given `Entity`.
     * 
     * A new instance of the given `Component` is constructed with the provided
     * arguments. 
     * 
     * @tparam ComponentType Type of the `Component` to be constructed.
     * @tparam Args Types of arguments for constructing the `Component`.
     * @param entity A rerfence to a `Entity`.
     * @param args The arguments for consturting the `Component`.
     * 
     * @return The newly constructed `Component`
     */
    template<typename ComponentType, typename... Args>
    [[maybe_unused]] auto &emplace(Entity &entity, Args &&...args)
    {
        auto id = getComponentSequenceID<ComponentType>();

        // Check if `Entity` already has one same `Component`, if so, return the 
        // existed one.
        if (entity._componentBitset[id] == true) {
            return *(entity._components[id]);
        }

        // constructing `Component`
        try {
            entity._components.emplace_back( std::make_unique<ComponentType>(entity, std::forward<Args>(args)...) );
        } catch (...) {
            throw;
        }
        
        // mapping `Entity` with the new `Component`
        entity._componentBitset[id] = true;
        _groups[id].emplace_back( &entity );

        return *(entity._components.back());
    }

    /**
     * @brief Removes the provided `Component` from the given `Entity`.
     * 
     * @tparam ComponentType The required removed `Component` type.
     * @param entity The given `Entity`.
     * @return If `Component` is removed successfully.
     */
    template<typename ComponentType>
    bool remove(Entity &entity)
    {
        auto id = getComponentSequenceID<ComponentType>();

        // `Entity` does not have provided `Component`
        if (entity._componentBitset[id] == false) {
            return 0;
        }
        
        // removes entity pointer from grouping
        __removeEntityFromGrouping(id, entity);

        // releases the actual component
        auto it = entity._components.begin() + id;
        entity._components.erase(it);
        entity._componentBitset[id] = false;
        
        return true;
    }

    /**
     * @brief Destroys the given `Entity` immediately and releases its 
     * `Component`s as well.
     * 
     * @warning If instant destruction is not required, please marks the 
     * `Entity` is disabled and calls Registry::refresh().
     * 
     * @param entity Provide an `Entity` for destroying.
     */
    void destroy(Entity &entity)
    {
        // removing each `Component` from grouping
        for (int i = 0; i < (int)MAX_COMPONENTS; ++i) {
            if (entity._componentBitset[i] == true) {
                __removeEntityFromGrouping(i, entity);
            }
        }

        // destroy the `Entity` at last
        _entities.erase(entity.getUUID());
    }

    /**
     * @brief Loops all the `Entity` and destroys all the inactive ones.
     * 
     * @warning From a internal perspective, after calling this function, the
     * order of the stored `Entity` does not retain.
     * 
     * @return std::size_t The number of destroyed `Entities`
     */
    std::size_t refresh()
    {
        std::size_t cnt = 0;
        for (auto &[id, entity] : _entities) {

            if (entity->isActive() == false) {
                destroy(*entity);
                ++cnt;
            }

        }
        return cnt;
    }

    /** @brief clears all the stored `Entity` and its corresponding `Component`. */
    void clear() 
    {
        _entities.clear();
        _groups.clear();
    }

    /** @brief Check is the given `Entity` has the provided `Component` */
    template<typename ComponentType>
    bool has(const Entity &entity) const
    {
        return entity._componentBitset[ getComponentSequenceID<ComponentType>() ];
    }

    /** @brief Return a reference of the required `Component` in the provide `Component` */
    template<typename ComponentType> 
    [[nodiscard]] ComponentType &get(Entity entity) const
    {
        return entity._components[ getComponentSequenceID<ComponentType>() ];
    }

    /**
     * @brief Returns a list of `Entities` which has the provided `ComponentTypes`
     * 
     * @tparam ComponentTypes The list of required `Component`s
     */
    template<typename... ComponentTypes>
    [[nodiscard]] std::vector<EntitieQueryGroup *> query()
    {
        static_assert(sizeof...(ComponentTypes) > 0, "must provide at least one Component type for querying");
        return std::vector<EntitieQueryGroup *> { __queryForEachComponent<ComponentTypes>()... };
    }

private:

    void __removeEntityFromGrouping(ComponentID id, Entity &entity)
    {
        auto &group = _groups[id];
        for (auto it = group.begin(); it != group.end(); ++it) {
            if (&entity == *it) {
                it = group.erase(it);
                return;
            }
        }
    }

    template<typename ComponentType>
    [[nodiscard]] EntitieQueryGroup *__queryForEachComponent()
    {
        auto &entities = _groups[ getComponentSequenceID<ComponentType>() ];
        return &entities;
    }

private:
    
    /** @brief stores the actual entities */
    std::map<EntityID, std::unique_ptr<Entity>> _entities;
    /** @brief grouping entities by their component type, easy for querying */
    std::unordered_map<ComponentID, EntitieQueryGroup> _groups;
};

} // AGE

#endif

