#include "ncurseAdapter.h"

namespace AGE
{
namespace Ncurses
{

/*******************************************************************************
 * @brief global Ncurses helper functions implementation
 ******************************************************************************/

void init(WindowOpt opt, bool echo)
{
    // initializes the screen
    // sets up memory and clears the screen
    initscr();
    
    switch (opt) 
    {
    case WindowOpt::CBREAK:
        cbreak();
        break;
    case WindowOpt::RAW:
        raw();
        break;
    default:
        cbreak();
        break;
    }
    
    if (!echo) {
        noecho();
    }
    
    // refreshes the screen to match whats in memory
    refresh();
}

void setInsantInput(const WindowBuffer &win, bool on)
{
    nodelay(win.getWin(), on);
}

void setInputTimeout(int tm)
{
    timeout(tm);
}

void setCursorVisibility(char visibility)
{
    curs_set(visibility);
}

void destroy()
{
    // deallocates memory and ends ncurses
    endwin();
}

/*******************************************************************************
 * @brief `WindowBuffer` implementation
 ******************************************************************************/

WindowBuffer::WindowBuffer(SIZE w, SIZE h, SIZE start_x, SIZE start_y)
    : _win { newwin(h, w, start_y, start_x) }, 
      _currPos {start_x, start_y},
      _w {static_cast<SIZE>(w)}, _h {static_cast<SIZE>(h)}
{}

WindowBuffer::~WindowBuffer() 
{
    // note: Ncurses::destory() will automatically destorys all all the WINDOWs
    // we do nothing here
}

WINDOW *WindowBuffer::getWin() const { return _win; }

void WindowBuffer::refresh()
{
    wrefresh(_win);
}

void WindowBuffer::showBorder(int top, int bottom, int left, int right, int corner)
{
    wborder(_win, left, right, top, bottom, corner, corner, corner, corner);
}

void WindowBuffer::print(std::string s, SIZE x, SIZE y)
{
    print(s.c_str(), x, y);
}

void WindowBuffer::print(const char *s, SIZE x, SIZE y)
{
    if ((x != -1) && (y != -1)) {
        moveTo(x, y);
    }
    wprintw(_win, s);
}

void WindowBuffer::moveTo(SIZE x, SIZE y)
{
    wmove(_win, y, x);
}

void WindowBuffer::erase() { werase(_win); }

void WindowBuffer::clear() { wclear(_win); }

vec2d<SIZE> WindowBuffer::currPosition() { return _currPos; }

SIZE WindowBuffer::width() { return _w; }

SIZE WindowBuffer::height() { return _h; }

} // Ncurses

} // AGE
