#include "collisionSystem.h"
#include "../registry/registry.h"
#include "../component/velocity.h"
#include "../component/position.h"

namespace AGE
{

CollisionSystem::CollisionSystem(Registry &registry): LogicSystem {registry} {}

CollisionSystem::~CollisionSystem() {}

void CollisionSystem::onUpdate()
{
    
}

} // AGE
