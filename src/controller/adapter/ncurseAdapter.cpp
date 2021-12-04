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

void setInsantInput(const Window &win, bool on)
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
 * @brief `Window` implementation
 ******************************************************************************/

Window::Window(SIZE w, SIZE h, SIZE start_x, SIZE start_y)
    : _win { newwin(h, w, start_y, start_x) }, 
      _currPos {start_x, start_y},
      _w {static_cast<SIZE>(w)}, _h {static_cast<SIZE>(h)}
{}

Window::~Window() 
{
    // note: Ncurses::destory() will automatically destorys all all the WINDOWs
    // we do nothing here
}

WINDOW *Window::getWin() const { return _win; }

void Window::refresh()
{
    wrefresh(_win);
}

void Window::showBorder(int top, int bottom, int left, int right, int corner)
{
    wborder(_win, left, right, top, bottom, corner, corner, corner, corner);
}

void Window::print(std::string s, SIZE x, SIZE y)
{
    print(s.c_str(), x, y);
}

void Window::print(const char *s, SIZE x, SIZE y)
{
    if ((x != -1) && (y != -1)) {
        moveTo(x, y);
    }
    wprintw(_win, s);
}

void Window::moveTo(SIZE x, SIZE y)
{
    wmove(_win, y, x);
}

void Window::erase() { werase(_win); }

void Window::clear() { wclear(_win); }

Point<SIZE> Window::currPosition() { return _currPos; }

SIZE Window::width() { return _w; }

SIZE Window::height() { return _h; }

} // Ncurses

} // AGE
