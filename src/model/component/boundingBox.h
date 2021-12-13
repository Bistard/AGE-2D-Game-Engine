/**
 * @file boundingBox.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-13
 */

#ifndef __AGE_BOUNDING_BOX__
#define __AGE_BOUNDING_BOX__

#include "component.h"
#include "../../common/vec2d.h"

namespace AGE
{

class CRectBox;

bool contains(const CRectBox &box, const vec2d<float> &pt);
bool intersects(const CRectBox &box1, const CRectBox &box2);

class CBoundingBox : public Component
{
public:
    CBoundingBox(Entity &entity): Component {entity} {}
    ~CBoundingBox() override {}
public:
    /**
     * @brief These functions are using 
     */
    virtual bool collideWith(const CRectBox &other) = 0;
};

class CRectBox : public CBoundingBox
{
public:
    CRectBox(Entity &entity, vec2d<float> leftTop, vec2d<float> rightBottom)
        : CBoundingBox {entity}, leftTop {leftTop}, rightBottom {rightBottom} 
    {}
    ~CRectBox() override {}
public:
    bool collideWith(const CRectBox &other) override
    {
        return intersects(*this, other);
    }
public:
    vec2d<float> leftTop;
    vec2d<float> rightBottom;
};

/** @brief determine if the point is inside the rectangle box. */
bool contains(const CRectBox &box, const vec2d<float> &pt)
{
    if ((box.leftTop.X() <= pt.X()) && (pt.X() <= box.rightBottom.X()) && 
        (box.leftTop.Y() <= pt.Y()) && (pt.Y() <= box.rightBottom.Y())) 
    {
        return true;
    }
    return false;
}

/** @brief determine if the two rectangle boxes intersects.  */
bool intersects(const CRectBox &box1, const CRectBox &box2)
{
    return contains(box1, box2.leftTop) || contains(box1, box2.rightBottom);
}

} // AGE


#endif
