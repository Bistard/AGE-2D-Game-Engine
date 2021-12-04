/**
 * @file grid.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __AGE_GRID__
#define __AGE_GRID__

#include <vector>
#include <stdint.h>

namespace AGE
{

/*******************************************************************************
 * @brief Abstract Based Class
 ******************************************************************************/
class Grid
{
public:
    Grid() = default;
    virtual ~Grid() = default;
public:
    // virtual 
};

struct Cell {
    int x;
    int y;
    uint8_t height;
};

// class SimpleGrid : public Grid
// {
// public:
//     SimpleGrid(SIZE width, SIZE height): Grid {}, _w {width}, _h {height} {}    
// public:
//     int getHeight(int x, int y) 
//     {
//         return _data.at(y).at(x).height;
//     }
// private:
//     std::vector<std::vector<Cell>> _data;
//     SIZE _w;
//     SIZE _h;
// };

} // AGE

#endif

