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
    auto [collidables] = _registry.query<CCollidable>();
    
    // time complexity: O( [n(n+1)]/2 ) -> O(n^2)
    for (auto it1 = collidables.begin(); it1 != std::prev(collidables.end()); ++it1) {
        Entity &e1 = **it1;
        CCollidable &c1 = _registry.get<CCollidable>(e1);

        for (auto it2 = std::next(it1); it2 != collidables.end(); ++it2) {
            Entity &e2 = **it2;
            CCollidable &c2 = _registry.get<CCollidable>(e2);

            CBoundingBox &b1 = c1.box;
            CBoundingBox &b2 = c2.box;

            // FIXME: this is a terrible design, fix this later
            if (b1.collideWith(static_cast<CRectBox &>(b2))) {
                for (auto onCollision : c1.onCollisionList) {
                    onCollision(e1, e2);
                }

                for (auto onCollision : c2.onCollisionList) {
                    onCollision(e2, e1);
                }
            }

        }

    }
}

} // AGE
