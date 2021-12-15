/**
 * @file math.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-02
 */

#ifndef __AGE_MATH__
#define __AGE_MATH__

#include <math.h>
#include "../common/vec2d.h"

namespace AGE
{

typedef unsigned char  SIZE; // 0 ~ 255
typedef unsigned short SSIZE; // 0 ~ 65,535

// round to the nearest integer position
vec2d<int> roundvec2d(const vec2d<float> &p);

bool contains(const vec2d<int> box, const vec2d<float> point);

} // AGE

#endif
