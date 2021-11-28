/*******************************************************************************
 * @file velocity.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-11-27
 ******************************************************************************/

#ifndef __AGE_VELOCITY__
#define __AGE_VELOCITY__

#include "point.h"

namespace AGE
{

class Velocity final
{
public:
    Velocity(float x, float y): _x {x}, _y {y} {}
    ~Velocity() = default;

    void add(const Velocity &v) noexcept { getX() += v.X(); getY() += v.Y(); }

    float X() const noexcept { return _x; }
    float Y() const noexcept { return _y; }

    void setX(float x) noexcept { _x = x; }
    void setY(float y) noexcept { _y = y; }
    
    float &getX() noexcept { return _x; }
    float &getY() noexcept { return _y; }

    const float &getX() const noexcept { return _x; }
    const float &getY() const noexcept { return _y; }
private:
    float _x;
    float _y;
};


} // AGE

#endif

