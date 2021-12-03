/**
 * @file rectObject.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-01
 */

#ifndef __AGE_RECT_OBJECT__
#define __AGE_RECT_OBJECT__

#include <string>
#include "objectModel.h"

namespace AGE
{

class RectObject : public ObjectModel
{
public:
    // pos1: left-top point
    // pos2: right-bottom point
    RectObject(Point<float> pos1, Point<float> pos2, std::string fill);
    ~RectObject() override;
public:
    void fill(std::string fill);
    void setPos1(Point<float> pos);
    void setPos2(Point<float> pos);

    const std::string &getFill() const noexcept;
    const Point<float> &getPos1() const noexcept;
    const Point<float> &getPos2() const noexcept;
private:
    Point<float> _pos1;
    Point<float> _pos2;
    std::string _fill;
};

} // AGE

#endif