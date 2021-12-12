#include "collisionSystem.h"

#include "../registry/registry.h"
#include "../component/velocity.h"
#include "../component/position.h"
#include "../component/collidable.h"

namespace AGE
{

CollisionSystem::CollisionSystem(Registry &registry): LogicSystem {registry} {}

CollisionSystem::~CollisionSystem() {}

void CollisionSystem::onUpdate()
{
    auto collidables = _registry.query<CCollidable>();

    // for (e1) {

    //     for (e2) {

    //         if CollisionHappens(e1, e2) {
                
    //             CCollidable &c1 = e1._components[ getComponentSequenceID<CCollidable>() ];
    //             CCollidable &c2 = e2._components[ getComponentSequenceID<CCollidable>() ];

    //             // handle logic
    //             c1.onCollision(e2);
    //             c2.onCollision(e1); // callable
    //         }
    //     }
    // }
}

} // AGE
