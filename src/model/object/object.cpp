#include "object.h"
#include "../../view/object/objectView.h"

namespace AGE
{

bool ObjectCompareAltitude::operator() (const Object *obj1, const Object *obj2)
{
    // smaller altitude pops out first
    return obj1->getAltitude() >= obj2->getAltitude();
}

/*******************************************************************************
 * @brief `ObjectDecorator` implementation
 ******************************************************************************/

ObjectDecorator::ObjectDecorator(std::shared_ptr<Object> obj): Object {}, _obj { std::move(obj) } {}

ObjectDecorator::~ObjectDecorator() {}

SIZE 
ObjectDecorator::getAltitude() const noexcept { return _obj->getAltitude(); }

void 
ObjectDecorator::setAltitude(char val) { _obj->setAltitude(val); }

ObjectView &
ObjectDecorator::getView() const noexcept { return _obj->getView(); }

Object &
ObjectDecorator::getObject() noexcept { return *_obj; }

/*******************************************************************************
 * @brief `Movable` implementation
 ******************************************************************************/

Movable::Movable(std::shared_ptr<Object> obj, Velocity val): 
    ObjectDecorator { obj }, _velocity {val} 
{}

Movable::~Movable() {}

Velocity Movable::getVelocity() const noexcept { return _velocity; }

void Movable::setVelocity(Velocity val) { _velocity = val; }

/*******************************************************************************
 * @brief `Gravitational` implementation
 ******************************************************************************/

Gravitational::Gravitational(std::shared_ptr<Object> obj, Velocity val): 
    Movable { obj }, _gravity {val} 
{}

Gravitational::~Gravitational() {}

Velocity Gravitational::getGravity() const noexcept { return _gravity; }

void Gravitational::setGravity(Velocity val) { _gravity = val; }

/*******************************************************************************
 * @brief `Collidable` implementation
 ******************************************************************************/

Collidable::Collidable(std::shared_ptr<Object> obj): ObjectDecorator {obj}, _box {} {}

Collidable::~Collidable() {}

/*******************************************************************************
 * @brief `NonCollidable` implementation
 ******************************************************************************/

NonCollidable::NonCollidable(std::shared_ptr<Object> obj): ObjectDecorator {obj} {}

NonCollidable::~NonCollidable() {}


} // AGE
