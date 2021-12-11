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
 * @brief 
 */
class Scene final
{
public:
    Scene() = default;
    ~Scene() = default;
public:
    Registry &getRegistry() { return _entityManager; }
    
    void onUpdate() 
    {
        for (auto &sys : _systems) {
            sys.onUpdate();
        }
    }
private:
    /** @brief the core component of the ECS */
    Registry _entityManager;
    /** @brief stores all the systems */
    std::vector<ISystem> _systems;
};

} // AGE


#endif
