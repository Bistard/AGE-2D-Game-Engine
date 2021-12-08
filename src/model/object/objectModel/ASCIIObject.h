/**
 * @file ASCIIObject.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-04
 */

#ifndef __AGE_ASCII_OBJECT__
#define __AGE_ASCII_OBJECT__

#include "../objectModel.h"

namespace AGE
{

/*******************************************************************************
 * @brief Concrete `ObjectModel` class - a single character object using 
 *  printable ASCII.
 ******************************************************************************/
class ASCIIObject : public ObjectModel
{
public:
    ASCIIObject(vec2d<float> pos, char ascii);
    ~ASCIIObject() override;
public:
    void setPos(vec2d<float> pos);
    vec2d<float> &getPos() noexcept;
    const vec2d<float> &getPos() const noexcept;

    void setASCII(char ascii) noexcept;
    char getASCII() const noexcept;

    // returns the position of the ascii character
    vec2d<float> &getPosition() override;
private:
    vec2d<float> _pos;
    char _ascii;
};

} // AGE

#endif
