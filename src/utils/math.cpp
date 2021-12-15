#include "math.h"

namespace AGE
{

vec2d<int> roundvec2d(const vec2d<float> &p)
{
    int x = static_cast<int>(p.X() + 0.5f);
    int y = static_cast<int>(p.Y() + 0.5f);
    return vec2d<int> {x, y};
}

bool contains(const vec2d<int> box, const vec2d<float> point)
{
    if (0 <= point.X() && point.X() <= box.X() && 
        0 <= point.Y() && point.Y() <= box.Y()) 
    {
        return true;
    }
    return false;
}

} // AGE
