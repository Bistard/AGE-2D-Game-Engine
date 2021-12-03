/**
 * @file math.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-02
 */

#ifndef __AGE_MATH__
#define __AGE_MATH__

#include "../common/point.h"

namespace AGE
{

typedef unsigned char  SIZE; // 0 ~ 255
typedef unsigned short SSIZE; // 0 ~ 65,535

// round to the nearest int position
Point<int> roundPoint(const Point<float> &p);

} // AGE

#endif
