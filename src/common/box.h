/*******************************************************************************
 * @file box.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-11-27
 ******************************************************************************/

#ifndef __AGE_BOX__
#define __AGE_BOX__

#include "vec2d.h"
#include <initializer_list>

namespace AGE
{

class Box final
{
public:
    Box(vec2d<int> leftTop, vec2d<int> rightBottom): _leftTop {leftTop}, _rightBottom {rightBottom} {}
    ~Box() = default;

    Box(std::initializer_list<vec2d<int>> ls): _leftTop {*ls.begin()}, _rightBottom {*(ls.begin() + 1)}
    {}

    bool contains(const vec2d<int> &p) const noexcept
    {
        if ((_leftTop.X() <= p.X()) && (p.X() <= _rightBottom.X()) && 
            (_leftTop.Y() <= p.Y()) && (p.Y() <= _rightBottom.Y())) 
        {
            return true;
        }
        return false;
    }

    bool intersects(const Box &b) const noexcept
    {
        return contains(b._leftTop) || contains(b._rightBottom);
    }

    void setLeftTop(vec2d<int> p) { _leftTop = p; }
    void setRightBottom(vec2d<int> p) { _rightBottom = p; }

    vec2d<int> &getLeftTop() noexcept { return _leftTop; }
    vec2d<int> &getRightBottom() noexcept { return _rightBottom; }
    const vec2d<int> &getLeftTop() const noexcept { return _leftTop; }
    const vec2d<int> &getRightBottom() const noexcept { return _rightBottom; }
private:
    vec2d<int> _leftTop;
    vec2d<int> _rightBottom;
};

} // AGE

#endif
