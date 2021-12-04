/**
 * @file rectObjectView.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-02
 */

#ifndef __AGE_RECT_OBJECT_VIEW__
#define __AGE_RECT_OBJECT_VIEW__

#include "objectView.h"
#include "../../model/object/rectObject.h"
#include "../../utils/math.h"

namespace AGE
{

class RectObjectView : public ObjectView
{
public:
    RectObjectView(RectObject &obj): ObjectView {obj} {}
    ~RectObjectView() override {}
public:
    void draw(Ncurses::Window &win) override
    {
        SIZE winWidth = win.width();
        SIZE winHeight = win.height();
        
        RectObject &obj = static_cast<RectObject &>(_obj);
        
        Point<int> pos1 = roundPoint(obj.getPos1());
        Point<int> pos2 = roundPoint(obj.getPos2());
        const std::string &fill = obj.getFill();
        
        for (SIZE x = pos1.X(); x < pos2.X(); ++x) {
            for (SIZE y = pos1.Y(); y < pos2.Y(); ++y) {
                // check if the character is outside of the screen
                if (0 <= x && x < winWidth && 0 <= y && y <= winHeight) {
                    win.print(fill.c_str(), x, y);
                }
            }
        }
    }
};

} // AGE


#endif
