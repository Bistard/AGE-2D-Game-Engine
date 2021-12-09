#include "object.h"
#include "../../view/object/objectView.h"

namespace AGE
{

bool ObjectCompareAltitude::operator() (const std::shared_ptr<Object> &obj1, const std::shared_ptr<Object> &obj2)
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

vec2d<float> &
ObjectDecorator::getPosition() { return _obj->getPosition(); }

Object &
ObjectDecorator::getObject() noexcept { return *_obj; }

/*******************************************************************************
 * @brief `Movable` implementation
 ******************************************************************************/

Movable::Movable(std::shared_ptr<Object> obj, vec2d<float> val): 
    ObjectDecorator { obj }, _velocity {val} 
{}

Movable::~Movable() {}

void 
Movable::setVelocity(vec2d<float> val) { _velocity = val; }

const vec2d<float> &
Movable::getVelocity() const noexcept { return _velocity; }

vec2d<float> &
Movable::getVelocity() noexcept { return _velocity; }

void 
Movable::updateData()
{
    _obj->updateData();
    _obj->getPosition() += _velocity;
}

/*******************************************************************************
 * @brief `Gravitational` implementation
 ******************************************************************************/

Gravitational::Gravitational(std::shared_ptr<Object> obj, vec2d<float> val): 
    Movable { obj }, _gravity {val} 
{}

Gravitational::~Gravitational() {}

void 
Gravitational::setGravity(vec2d<float> val) { _gravity = val; }

const vec2d<float> &
Gravitational::getGravity() const noexcept { return _gravity; }

vec2d<float> &
Gravitational::getGravity() noexcept { return _gravity; }

void 
Gravitational::updateData()
{
    _obj->updateData();
    _obj->getPosition() += this->getVelocity();
    _obj->getPosition() += _gravity;
}

/*******************************************************************************
 * @brief `Collidable` implementation
 ******************************************************************************/

// Collidable::Collidable(std::shared_ptr<Object> obj): ObjectDecorator {obj}, _box {} {} // FIX: how to construct a coressponding Box based on the Object type
// Collidable::Collidable(std::shared_ptr<RectObject> obj) {}
// Collidable::Collidable(std::shared_ptr<ASCIIObject> obj) {}
// Collidable::Collidable(std::shared_ptr<BitmapObject> obj) {}

Collidable::~Collidable() {}

void
Collidable::updateData() 
{
    _obj->updateData();
}

void 
Collidable::onCollision() {}

/*******************************************************************************
 * @brief `NonCollidable` implementation
 ******************************************************************************/

NonCollidable::NonCollidable(std::shared_ptr<Object> obj): ObjectDecorator {obj} {}

NonCollidable::~NonCollidable() {}

void
NonCollidable::updateData() {}

} // AGE
