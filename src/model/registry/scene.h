/**
 * @file scene.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-11
 */

#ifndef __AGE_SCENE__
#define __AGE_SCENE__

#include <vector>
#include "../registry/registry.h"
#include "../system/system.h"

namespace AGE
{

/**
 * @brief Scene is essentially a wrapper class for ECS.
 */
class Scene final
{
public:
    Scene() = default;
    ~Scene() = default;
public:
    Registry &getRegistry() { return _registry; }
    
    /**
     * @brief Emplaces a new `System` inside the `Scene`. The new system shares
     * the same lifetime with the `Scene`.
     * 
     * @tparam SystemType The type of the `System`.
     * @tparam Args The list of argument types to construct a new `System`.
     * @param args The actual arguments for constructing the new `System`.
     */
    template<typename SystemType, typename... Args>
    void emplaceSystem(Args &&...args)
    {
        static_assert(std::is_base_of<System, SystemType>::value);
        _systems.emplace_back( std::make_unique<SystemType>(std::forward<Args>(args)...) );
    }

    /** @brief calls System::onUpdate() for each `System`. */
    void onUpdate() 
    {
        for (auto &sys : _systems) {
            sys->onUpdate();
        }
    }
private:
    /** @brief the core component of the ECS */
    Registry _registry;
    /** @brief stores all the systems */
    std::vector<std::unique_ptr<System>> _systems;
};

} // AGE


#endif
