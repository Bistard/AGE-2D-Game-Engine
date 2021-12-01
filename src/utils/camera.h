/**
 * @file camera.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __AGE_CAMERA__
#define __AGE_CAMERA__

#include "../common/point.h"

namespace AGE
{

class Camera
{
public:
    Camera(Point<int> pos, int width, int height): position {pos}, width {width}, height {height} {}
    ~Camera() = default;
public:
    // positive: move right  
    // negative: move left
    void moveH(int steps) { position.getX() += steps; }
    // positive: move up  
    // negative: move down
    void moveV(int steps) { position.getY() -= steps; }
public:
    Point<int> position;
    const int width;
    const int height;
};

} // AGE


#endif

