/**
 * @file object.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.2
 * @date 2021-12-04
 */

#ifndef __AGE_OBJECT__
#define __AGE_OBJECT__

#include <memory>

#include "../../common/box.h"
#include "../../common/point.h"
#include "../../common/velocity.h"
#include "../../utils/math.h"

namespace AGE
{

class ObjectView;

/*******************************************************************************
 * @brief Base Interface Class
 ******************************************************************************/
class Object
{
public:
    virtual SIZE getAltitude() const noexcept = 0;
    virtual void setAltitude(char val) = 0;
    virtual ObjectView &getView() const noexcept = 0;
};

// class for sorting `Object`
class ObjectCompareAltitude
{
public:
    bool operator() (const Object *obj1, const Object *obj2);
};

/*******************************************************************************
 * @brief Object Decorator(s)
 *  - Movable
 *  - Gravitational (ALSO movable)
 *  - Collidable
 *  - NonCollidable
 ******************************************************************************/

class ObjectDecorator : public Object
{
public:
    ObjectDecorator(std::shared_ptr<Object> obj);
    virtual ~ObjectDecorator();
public:
    SIZE getAltitude() const noexcept override;
    void setAltitude(char val) override;
    ObjectView &getView() const noexcept override;
    Object &getObject() noexcept;
protected:
    std::shared_ptr<Object> _obj;
};

class Movable : public ObjectDecorator
{
public:
    Movable(std::shared_ptr<Object> obj, Velocity val = {0.0f, 0.0f});
    ~Movable() override;
public:
    Velocity getVelocity() const noexcept;
    void setVelocity(Velocity val);
private:
    Velocity _velocity;
};

class Gravitational : public Movable
{
public:
    Gravitational(std::shared_ptr<Object> obj, Velocity val = {0.0f, 0.0f});
    ~Gravitational() override;
public:
    Velocity getGravity() const noexcept;
    void setGravity(Velocity val);
private:
    Velocity _gravity;
};

class Collidable : public ObjectDecorator // FIX: unfinished
{
public:
    Collidable(std::shared_ptr<Object> obj);
    ~Collidable() override;
private:
    Box _box;
};

class NonCollidable : public ObjectDecorator
{
public:
    NonCollidable(std::shared_ptr<Object> obj);
    ~NonCollidable() override;
};


} // AGE


#endif
