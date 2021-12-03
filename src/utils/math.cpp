#include "math.h"

namespace AGE
{

Point<int> roundPoint(const Point<float> &p)
{
    int x = static_cast<int>(p.X() + 0.5f);
    int y = static_cast<int>(p.Y() + 0.5f);
    return Point<int> {x, y};
}

} // AGE
