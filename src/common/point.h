/*******************************************************************************
 * @file point.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-11-27
 ******************************************************************************/

#ifndef __AGE_POINT__
#define __AGE_POINT__

#include <initializer_list>

#define AGE_DEFAULT_WIN_WIDTH 80
#define AGE_DEFAULT_WIN_HEIGHT 25

typedef unsigned short SIZE; // 0 ~ 255

namespace AGE
{

template<typename T = int> // T = float
class Point final
{
public:
    Point(T x, T y): _x {x}, _y {y} {}
    Point(std::initializer_list<T> ls) 
    {
        _x = *ls.begin();
        _y = *(ls.begin() + 1);
    }
    ~Point() {};

    T X() const noexcept { return _x; }
    T Y() const noexcept { return _y; }

    void setX(T x) noexcept { _x = x; }
    void setY(T y) noexcept { _y = y; }
    
    T &getX() noexcept { return _x; }
    T &getY() noexcept { return _y; }

    const T &getX() const noexcept { return _x; }
    const T &getY() const noexcept { return _y; }
private:
    T _x;
    T _y;
};

} // AGE

#endif
