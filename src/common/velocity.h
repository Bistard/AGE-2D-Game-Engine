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

class Velocity : public Point<float>
{
public:
    Velocity(float x, float y): Point {x, y} {}
    ~Velocity() = default;

    void add(const Velocity &v) noexcept { getX() += v.X(); getY() += v.Y(); }
};


} // AGE

#endif

