/**
 * @file boundingBox.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-13
 */

#ifndef __AGE_BOUNDING_BOX__
#define __AGE_BOUNDING_BOX__

#include "component.h"
#include "position.h"
#include "../../common/vec2d.h"

namespace AGE
{

class CRectBox;

bool contains(const CRectBox &box, const vec2d<float> &pt);
bool intersects(const CRectBox &box1, const CRectBox &box2);

class CBoundingBox : public Component
{
public:
    CBoundingBox(Entity &entity, CPosition &pos): Component {entity}, pos {pos} {}
    ~CBoundingBox() override {}
public:
    virtual bool collideWith(const CRectBox &other) = 0;
public:
    CPosition &pos;
};


class CRectBox : public CBoundingBox
{
public:
    CRectBox(Entity &entity, CPosition &pos, float width, float height)
        : CBoundingBox {entity, pos}, width {width}, height {height}
    {}
    ~CRectBox() override {}
public:
    bool collideWith(const CRectBox &other) override
    {
        return intersects(*this, other);
    }
public:
    float width, height;
};

} // AGE


#endif
