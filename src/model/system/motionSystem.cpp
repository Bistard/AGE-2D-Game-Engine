#include "motionSystem.h"
#include "../registry/registry.h"
#include "../component/velocity.h"
#include "../component/position.h"

namespace AGE
{

MotionSystem::MotionSystem(Registry &registry): LogicSystem {registry} {}

MotionSystem::~MotionSystem() {}

void MotionSystem::onUpdate()
{
    auto entities = _registry.query<CVelocity>();
}

} // AGE
