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
    void emplaceLogicSystem(Args &&...args)
    {
        static_assert(std::is_base_of<LogicSystem, SystemType>::value);
        _logicSystems.emplace_back( std::make_unique<SystemType>(std::forward<Args>(args)...) );
    }

    /** @brief same as `emplaceLogicSystem`. */
    template<typename SystemType, typename... Args>
    void emplaceViewSystem(Args &&...args)
    {
        static_assert(std::is_base_of<ViewSystem, SystemType>::value);
        _viewSystems.emplace_back( std::make_unique<SystemType>(std::forward<Args>(args)...) );
    }

    /** @brief calls System::onUpdate() for each `LogicSystem`. */
    void updateLogicSystems(float elapse) 
    {
        for (auto &sys : _logicSystems) {
            sys->setElapse(elapse);
            sys->onUpdate();
        }
    }

    /** @brief calls System::onUpdate() for each `ViewSystem`. */
    void updateViewSystems() 
    {
        for (auto &sys : _viewSystems) {
            sys->onUpdate();
        }
    }
private:
    /** @brief the core component of the ECS */
    Registry _registry;
    /** @brief stores all the systems */
    std::vector<std::unique_ptr<LogicSystem>> _logicSystems;
    std::vector<std::unique_ptr<ViewSystem>> _viewSystems;
};

} // AGE


#endif
