/**
 * @file bitmap.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-04
 */

#ifndef __AGE_BITMAP__
#define __AGE_BITMAP__

#include <initializer_list>
#include <vector>

namespace AGE
{

template<typename T>
struct Triple final
{
    Triple(int x, int y, T data): x {x}, y {y}, data {data} {}

    int x, y;
    T data;
};

template<typename T>
class Bitmap final
{
public:
    Bitmap(std::initializer_list<T> ls);
private:
    std::vector< std::vector<T> > _map;
};

} // AGE


#endif
