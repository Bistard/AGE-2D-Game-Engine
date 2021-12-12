/**
 * @file ncurseAdapter.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief The adapter class for the Ncurses library which is more friendly 
 *   with C++.
 * @version 0.1
 * @date 2021-11-27
 */

#ifndef __AGE_NCURSE_ADAPTER__
#define __AGE_NCURSE_ADAPTER__

#include <memory>
#include <string>

#include <ncurses.h>

#include "../../common/vec2d.h"
#include "../../utils/math.h"

#define NCURSE_ERR ERR
#define NCURSE_OK OK

namespace AGE
{

/*******************************************************************************
 * @brief wraper functions that encapsulate Ncurses library
 ******************************************************************************/
namespace Ncurses
{

class WindowBuffer;
enum WindowOpt
{
    CBREAK = 0, // NO BUFFERING. User hits is returned immediately
    RAW
};

enum CurseVisibility
{
    INVISIBLE = 0,
    NORMAL    = 1, 
    VISIBLE   = 2
};

/**
 * @brief Initializes the screen and sets up memory. Must be called before using 
 *   Ncurses.
 * @param opt options for setting up a window
 * @param echo if user typing will echo on the screen
 */
void init(WindowOpt opt = WindowOpt::CBREAK, bool echo = false);

// 0, 1, 2 for invisible, normal, or very visible respectively
void setCursorVisibility(char visibility = 0);

/**
 * @brief turn instant input mode on or off.
 *        No inputs return ERR (-1).
 * @param win the target window
 * @param on true -> instant input
 */
void setInsantInput(const WindowBuffer &win, bool on);

/**
 * @brief Set input mode with a timeout.
 *        No inputs return ERR (-1).
 * @param timeout milliseconds
 */
void setInputTimeout(int timeout);

/**
 * @brief deallocates memory and ends ncurses. Must be called after finish using
 *   everything.
 */
void destroy();

/*******************************************************************************
 * @brief Adapter class for wrapping Ncurses WINDOW - C++ friendly
 ******************************************************************************/
class WindowBuffer
{ 
public:
    // you need to call `refresh()` from Ncurses libarary manually if you are 
    //   constructing a `WindowBuffer`.
    WindowBuffer(SIZE w, SIZE h, SIZE start_x, SIZE start_y);
    ~WindowBuffer();

    WINDOW *getWin() const;
    vec2d<SIZE> currPosition();
    SIZE width();
    SIZE height();

    void print(std::string s, SIZE x = -1, SIZE y = -1);
    void print(const char *s, SIZE x = -1, SIZE y = -1);
    void showBorder(int top = 32, int bottom = 32, int left = 32, int right = 32, int corner = 32);
    void moveTo(SIZE x, SIZE y);
    void refresh(); // refresh this window
    
    void erase(); // clears this window screen
    void clear(); // clears this window screen (hard clear)
private:
    WINDOW *_win;
    vec2d<SIZE> _currPos;
    SIZE _w;
    SIZE _h;
};

} // Ncurses

} // AGE

#endif
