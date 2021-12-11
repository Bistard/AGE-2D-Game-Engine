#include "entity.h"
#include "../../utils/uuid.h"
#include "../component/component.h"
#include "../registry/registry.h"

namespace AGE
{

Entity::Entity(Registry &registry): _uuid { UUID {} }, _registry {registry} {}

Entity::~Entity() {}

const EntityID
Entity::getUUID() const noexcept { return _uuid; }

void 
Entity::update() {}

void 
Entity::destroy() noexcept { _active = false; }

bool 
Entity::isActive() const noexcept { return _active; }

Registry &
Entity::getRegistry() { return _registry; }

} // AGE
