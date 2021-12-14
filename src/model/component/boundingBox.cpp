#include "boundingBox.h"

namespace AGE
{

/** @brief determine if the point is inside the rectangle box. */
bool contains(const CRectBox &box, const CPosition &pt)
{
    if ((box.pos.val.X() <= pt.val.X()) && (pt.val.X() <= box.pos.val.X()) && 
        (box.pos.val.Y() <= pt.val.Y()) && (pt.val.Y() <= box.pos.val.Y())) 
    {
        return true;
    }
    return false;
}

/** @brief determine if the two rectangle boxes intersects.  */
bool intersects(const CRectBox &box1, const CRectBox &box2)
{
    return contains(box1, box2.pos) || contains(box1, box2.pos);
}

} // AGE
