/**
 * @file asciiObjectView.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-04
 */

#ifndef __AGE_ASCII_OBJECT_VIEW__
#define __AGE_ASCII_OBJECT_VIEW__

#include "objectView.h"
#include "../../model/object/objectModel/ASCIIObject.h"
#include "../../utils/math.h"

namespace AGE
{

class ASCIIObjectView : public ObjectView
{
public:
    ASCIIObjectView(ASCIIObject &obj): ObjectView {obj} {}
    ~ASCIIObjectView() override {}
public:
    void draw(Ncurses::Window &win) override
    {
        SIZE winWidth = win.width();
        SIZE winHeight = win.height();
        
        ASCIIObject &obj = static_cast<ASCIIObject &>(_obj);
        
        vec2d<int> pos = roundvec2d(obj.getPos());
        std::string ascii { static_cast<char>(obj.getASCII()) };
        
        if (0 <= pos.X() && pos.X() < winWidth && 0 <= pos.Y() && pos.Y() <= winHeight) {
            win.print(ascii.c_str(), pos.X(), pos.Y());
        }
    }
};

} // AGE


#endif
