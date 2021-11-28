/*******************************************************************************
 * @file box.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-11-27
 ******************************************************************************/

#ifndef __AGE_BOX__
#define __AGE_BOX__

#include "point.h"

namespace AGE
{

class Box final
{
public:
    Box(Point<int> leftTop, Point<int> rightBottom): _leftTop {leftTop}, _rightBottom {rightBottom} {}
    
    bool contains(const Point<int> &p) const noexcept
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

    void setLeftTop(Point<int> p) { _leftTop = p; }
    void setRightBottom(Point<int> p) { _rightBottom = p; }

    Point<int> &getLeftTop() noexcept { return _leftTop; }
    Point<int> &getRightBottom() noexcept { return _rightBottom; }
    const Point<int> &getLeftTop() const noexcept { return _leftTop; }
    const Point<int> &getRightBottom() const noexcept { return _rightBottom; }
private:
    Point<int> _leftTop;
    Point<int> _rightBottom;
};

} // AGE

#endif
