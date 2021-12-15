/**
 * @file motion.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-15
 */

#ifndef __AGE_MOTION_COMPONENT__
#define __AGE_MOTION_COMPONENT__

#include "component.h"
#include "velocity.h"
#include "position.h"
#include "../../utils/math.h"

namespace AGE
{

class CMotionType;

class CMotion : public Component
{
public:
    CMotion(Entity &entity, CMotionType &type): Component {entity}, type {type} {}
    ~CMotion() override {}
public:
    void update(int elapse) { type.update(elapse); }
public:
    CMotionType &type;
};

class CMotionType : public Component
{
public:
    CMotionType(Entity &entity, CPosition &position): Component {entity}, position {position} {}
    ~CMotionType() override {}
public:
    virtual void update(int elapse) = 0;
public:
    CPosition &position;
};

class CStraightMotion : public CMotionType
{
public:
    CStraightMotion(Entity &entity, CPosition &position, float dx, float dy)
        : CMotionType {entity, position}, velocity {dx, dy}
    {}
    ~CStraightMotion() override {}
public:
    void update(int elapse) override
    {
        position.val.getX() += velocity.X() * elapse;
        position.val.getY() += velocity.Y() * elapse;
    }
public:
    vec2d<float> velocity;
};

class CCircleMotion : public CMotionType
{
public:
    CCircleMotion(Entity &entity, CPosition &position, float radius, float orbitSpeed)
        : CMotionType {entity, position}, radius {radius}, orbitSpeed {orbitSpeed}
    {}
    ~CCircleMotion() override {}
public:
    void update(int elapse) override
    {
        angle += orbitSpeed * elapse;
        position.val.getX() += radius * cos(angle);
        position.val.getY() += radius * sin(angle);
    }
public:
    float radius;
    float orbitSpeed;
    float angle;
};

} // AGE


#endif
