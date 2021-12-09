/**
 * @file rectObject.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-01
 */

#ifndef __AGE_RECT_OBJECT__
#define __AGE_RECT_OBJECT__

#include <string>
#include "../objectModel.h"

namespace AGE
{

/*******************************************************************************
 * @brief Concrete `ObjectModel` class - represent a rectangle object made up by 
 *  a single character repeated.
 ******************************************************************************/
class RectObject : public ObjectModel
{
public:
    // pos1: left-top vec2d
    // pos2: right-bottom vec2d
    RectObject(vec2d<float> pos1, vec2d<float> pos2, std::string fill);
    RectObject(vec2d<float> pos, float width, float height, std::string fill);
    ~RectObject() override;
public:
    void setFill(std::string fill);
    void setPosition(vec2d<float> pos);
    void setWidth(float width);
    void setHeight(float width);
    
    // returns the left-top vec2d of the rectangle.
    vec2d<float> &getPosition() override;
    float getWidth() const noexcept;
    float getHeight() const noexcept;
    std::string &getFill() noexcept;
    const std::string &getFill() const noexcept;
private:
    vec2d<float> _pos;
    float _w;
    float _h;
    std::string _fill;
};

} // AGE

#endif
