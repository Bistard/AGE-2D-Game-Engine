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

void destroy()
{
    // deallocates memory and ends ncurses
    endwin();
}

std::unique_ptr<Window> newWindow(int w, int h, int start_x, int start_y)
{
    std::unique_ptr<Window> window { new Window {w, h, start_x, start_y} };

    refresh(); // let the console knows a new window is created
    return window;
}

/*******************************************************************************
 * @brief `Window` implementation
 ******************************************************************************/

Window::Window(int w, int h, int start_x, int start_y)
    : _win { newwin(h, w, start_y, start_x) }, 
      _currPos {start_x, start_y},
      _w {static_cast<short>(w)}, _h {static_cast<short>(h)}
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

void Window::showBorder(int top, int side, int corner)
{
    wborder(_win, side, side, top, top, corner, corner, corner, corner);
    refresh(); // refreshes the specific WINDOW
}

void Window::print(std::string s, int x, int y)
{
    if ((x != -1) && (y != -1)) {
        moveTo(y, x);
    }
    wprintw(_win, s.c_str());
    refresh();
}

void Window::moveTo(int x, int y)
{
    wmove(_win, y, x);
}

void Window::clean() { wclear(_win); }

Point<int> Window::currPosition() { return _currPos; }

short Window::width() { return _w; }

short Window::height() { return _h; }

} // Ncurses

} // AGE
