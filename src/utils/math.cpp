#include "math.h"

namespace AGE
{

vec2d<int> roundvec2d(const vec2d<float> &p)
{
    int x = static_cast<int>(p.X() + 0.5f);
    int y = static_cast<int>(p.Y() + 0.5f);
    return vec2d<int> {x, y};
}

} // AGE
