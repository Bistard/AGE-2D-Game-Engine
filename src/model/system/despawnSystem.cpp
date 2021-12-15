#include "despawnSystem.h"
#include "../registry/registry.h"
#include "../component/global/windowInfo.h"
#include "../component/despawn.h"
#include "../../utils/math.h"

namespace AGE
{

DespawnSystem::DespawnSystem(Registry &registry): LogicSystem {registry} {}

DespawnSystem::~DespawnSystem() {}

void 
DespawnSystem::onUpdate()
{
    auto [despawns] = _registry.query<CDespawn>();
    
    CWindowInfo *info = nullptr;
    try {
        info = &_registry.queryGlobal<CWindowInfo>();
    } catch (...) {
        /** @brief no provided `CWindowInfo`. Since we do not have own logger 
         * system, we simply throws exception. */
        throw;
    }
    
    
    for (auto e : despawns) {
        CDespawn &despawn = _registry.get<CDespawn>(*e);
        
        // the despawn entity is not in the sight of the window
        if (contains(info->dimension, despawn.pos.val) == false) {

            ++despawn.count;

            if (despawn.count == despawn.tickMax) {
                /** 
                 * @brief The reason we do not use Registry::destroy() here is 
                 * beacuse it will interupts the iterator during the current for
                 * loop. For solve this, we mark the entity as disabled and 
                 * destroy all the disabled ones by using Registry::destroy() 
                 */
                (*e).disable();
            }

        }
    }

    // see above comment
    _registry.refresh();
}

} // AGE
