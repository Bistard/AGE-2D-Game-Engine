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
        
        if (contains(info->dimension, despawn.pos.val)) {

            ++despawn.count;

            if (despawn.count == despawn.tickMax) {
                _registry.destroy(*e);
            }

        }
    }
}

} // AGE