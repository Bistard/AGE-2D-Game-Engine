/*******************************************************************************
 * @file vec2d.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-11-27
 ******************************************************************************/

#ifndef __AGE_VEC_2D__
#define __AGE_VEC_2D__

#include <initializer_list>

#define AGE_DEFAULT_WIN_WIDTH 80
#define AGE_DEFAULT_WIN_HEIGHT 25

namespace AGE
{

template<typename T = int> // T = float
class vec2d final
{
public:
    vec2d(T x, T y): _x {x}, _y {y} {}
    vec2d(std::initializer_list<T> ls) 
    {
        _x = *ls.begin();
        _y = *(ls.begin() + 1);
    }
    ~vec2d() {};
    
    vec2d<T> &operator+=(vec2d<T> other) 
    {
        _x += other._x;
        _y += other._y;
        return *this;
    }

    vec2d<T> operator+(const vec2d<T> &other) const
    {
        return vec2d<T> { _x + other._x, _y + other._y };
    }

    vec2d<T> &operator-=(vec2d<T> other) 
    {
        _x -= other._x;
        _y -= other._y;
        return *this;
    }

    vec2d<T> operator-(const vec2d<T> &other) const
    {
        return vec2d<T> { _x - other._x, _y - other._y };
    }
public:
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
