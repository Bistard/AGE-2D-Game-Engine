#include "motionSystem.h"
#include "../registry/registry.h"
#include "../component/velocity.h"
#include "../component/gravity.h"
#include "../component/position.h"

namespace AGE
{

MotionSystem::MotionSystem(Registry &registry): LogicSystem {registry} {}

MotionSystem::~MotionSystem() {}

void MotionSystem::onUpdate()
{
    auto [velocities, gravities] = _registry.query<CVelocity, CGravity>();
    
    // updates velocity value onto its position
    for (auto e : velocities) {
        CVelocity &velocity = _registry.get<CVelocity>(*e);
        CPosition &position = _registry.get<CPosition>(*e);
        
        position.pos.getX() += velocity.val.X() * _elapse;
        position.pos.getY() += velocity.val.Y() * _elapse;
    }
    
    // updates gravitational acceleration onto its velocity
    for (auto e : gravities) {
        CGravity &gravity = _registry.get<CGravity>(*e);
        CVelocity &velocity = _registry.get<CVelocity>(*e);
        
        velocity.val.getX() += gravity.acceleration.X() * _elapse;
        velocity.val.getY() += gravity.acceleration.Y() * _elapse;
    }
}

} // AGE
