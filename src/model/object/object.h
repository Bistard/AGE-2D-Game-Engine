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
#include "../../common/vec2d.h"
#include "../../utils/math.h"

namespace AGE
{

class ObjectView;
class RectObject;
class ASCIIObject;
class BitmapObject;

/*******************************************************************************
 * @brief Base Interface Class
 ******************************************************************************/
class Object
{
public:
    virtual SIZE getAltitude() const noexcept = 0;
    virtual void setAltitude(char val) = 0;
    virtual ObjectView &getView() const noexcept = 0;
    virtual vec2d<float> &getPosition() = 0;
    
    /**
     * @brief updates its own data according to the inherited features. 
     * 
     * For instances, 
     *  - if `Movable` inherits `Object`, updateData() gets override and each 
     *      call will change its position by its velocity. 
     *  - If `Gravitational` inherits `Object`, updateData() gets override and
     *      each call will change its position by its gravitational velocity.
     */
    virtual void updateData() = 0;
};

// class for sorting `Object`
class ObjectCompareAltitude
{
public:
    bool operator() (const std::shared_ptr<Object> &obj1, const std::shared_ptr<Object> &obj2);
};

/*******************************************************************************
 * @brief Object Decorator(s)
 *  - Movable
 *  - Gravitational (ALSO movable)
 *  - Collidable
 *  - NonCollidable
 ******************************************************************************/

// asbtract class
class ObjectDecorator : public Object
{
public:
    ObjectDecorator(std::shared_ptr<Object> obj);
    virtual ~ObjectDecorator();
public:
    SIZE getAltitude() const noexcept override;
    void setAltitude(char val) override;
    ObjectView &getView() const noexcept override;
    vec2d<float> &getPosition() override;
    Object &getObject() noexcept;
    /* virtual void updateData() = 0; */
protected:
    std::shared_ptr<Object> _obj;
};

// concrete object decorator
class Movable : public ObjectDecorator
{
public:
    Movable(std::shared_ptr<Object> obj, vec2d<float> val = {0.0f, 0.0f});
    ~Movable() override;
public:
    void setVelocity(vec2d<float> val);
    const vec2d<float> &getVelocity() const noexcept;
    vec2d<float> &getVelocity() noexcept;
    void updateData() override;
private:
    vec2d<float> _velocity;
};

// concrete object decorator
class Gravitational : public Movable
{
public:
    Gravitational(std::shared_ptr<Object> obj, vec2d<float> val = {0.0f, 0.0f});
    ~Gravitational() override;
public:
    void setGravity(vec2d<float> val);
    const vec2d<float> &getGravity() const noexcept;
    vec2d<float> &getGravity() noexcept;
    void updateData() override;
private:
    vec2d<float> _gravity;
};

// concrete object decorator
class Collidable : public ObjectDecorator
{
public:
     
    ~Collidable() override;
public:
    bool collidesWith(const Object &other);
    virtual void onCollision();
public:
    void updateData() override;
private:
    Box _box;
};

// concrete object decorator
class NonCollidable : public ObjectDecorator
{
public:
    NonCollidable(std::shared_ptr<Object> obj);
    ~NonCollidable() override;
public:
    void updateData() override;
};


} // AGE


#endif
